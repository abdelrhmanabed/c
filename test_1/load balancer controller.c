#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <semaphore.h>
#include <fcntl.h>

#define MAX_SLAVES 10
#define SHM_KEY 1234
#define MSG_KEY_CTRL 5678
#define MSG_KEY_REPORT 9876
#define SEM_NAME "/load_sem"

typedef struct {
    long mtype;
    int job_id;
} JobRequest;

typedef struct {
    long mtype;
    int slave_id;
} SlaveResponse;

typedef struct {
    long mtype;
    int slave_id;
    int cpu_used;
    int time_used;
} JobReport;

typedef struct {
    int num_slaves;
    int max_cpu;
    int max_time;
    int max_runtime;
    int cpu_used[MAX_SLAVES];
    int time_used[MAX_SLAVES];
    int terminate;
    pid_t slave_pids[MAX_SLAVES];
    char slave_ips[MAX_SLAVES][16];
} SharedData;

SharedData *shared = NULL;
sem_t *sem = NULL;
int shm_id, msgid_ctrl, msgid_report;
volatile int running = 1;

void sigterm_handler(int sig) {
    running = 0;
}

int get_elapsed_time() {
    static time_t start_time = 0;
    if (start_time == 0)
        start_time = time(NULL);
    return (int)(time(NULL) - start_time);
}

int find_least_loaded_slave() {
    int idx = 0;
    int min_load = shared->cpu_used[0];

    for (int i = 1; i < shared->num_slaves; ++i) {
        if (shared->cpu_used[i] < min_load) {
            min_load = shared->cpu_used[i];
            idx = i;
        }
    }
    return idx;
}

void process_job_request() {
    JobRequest request;
    if (msgrcv(msgid_ctrl, &request, sizeof(JobRequest) - sizeof(long), 1, IPC_NOWAIT) != -1) {
        sem_wait(sem);
        int selected_slave = find_least_loaded_slave();
        sem_post(sem);

        SlaveResponse response = {
            .mtype = request.mtype,
            .slave_id = selected_slave
        };

        if (msgsnd(msgid_ctrl, &response, sizeof(SlaveResponse) - sizeof(long), 0) == -1) {
            perror("[LoadBalancer] Failed to send response to master");
        }
    }
}

void process_job_report() {
    JobReport report;
    if (msgrcv(msgid_report, &report, sizeof(JobReport) - sizeof(long), 1, IPC_NOWAIT) != -1) {
        sem_wait(sem);
        shared->cpu_used[report.slave_id] += report.cpu_used;
        shared->time_used[report.slave_id] += report.time_used;
        sem_post(sem);
    }
}

int check_termination_conditions() {
    sem_wait(sem);

    for (int i = 0; i < shared->num_slaves; ++i) {
        if (shared->cpu_used[i] >= shared->max_cpu ||
            shared->time_used[i] >= shared->max_time) {

            printf("[LoadBalancer] Slave %d exceeded limits (CPU=%d, Time=%d)\n",
                   i, shared->cpu_used[i], shared->time_used[i]);

            shared->terminate = 1;
            sem_post(sem);
            return 1;
        }
    }

    if (get_elapsed_time() >= shared->max_runtime) {
        printf("[LoadBalancer] Simulation time limit reached.\n");
        shared->terminate = 1;
        sem_post(sem);
        return 1;
    }

    sem_post(sem);
    return 0;
}

void setup_ipc() {
    shm_id = shmget(SHM_KEY, sizeof(SharedData), 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shared = (SharedData *)shmat(shm_id, NULL, 0);
    if (shared == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    msgid_ctrl = msgget(MSG_KEY_CTRL, 0666 | IPC_CREAT);
    msgid_report = msgget(MSG_KEY_REPORT, 0666 | IPC_CREAT);
    if (msgid_ctrl == -1 || msgid_report == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
}

void cleanup_resources() {
    shmdt(shared);
    sem_close(sem);
    printf("[LoadBalancer] Exiting. IPC cleanup is handled by the main process.\n");
}

int main() {
    signal(SIGTERM, sigterm_handler);
    setup_ipc();

    while (running) {
        process_job_request();
        process_job_report();

        if (check_termination_conditions()) {
            break;
        }

        usleep(100000); // sleep for 100ms
    }

    cleanup_resources();
    return 0;
}
