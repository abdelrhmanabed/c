//Abdelrhman Abed 1193191
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#define MS 100
typedef struct {
    int start_row;
    int end_row;
    int matrix_a[MS][MS];
    int matrix_b[MS][MS];
    int result[MS][MS];
} thread_data;

void* worker_thread(void* arg) {
    thread_data* data = (thread_data*)arg;

    for (int i = data->start_row; i < data->end_row; ++i) {
        for (int j = 0; j < MS; ++j) {
            data->result[i][j] = 0;
            for (int k = 0; k < MS; ++k) {
                data->result[i][j] += data->matrix_a[i][k] * data->matrix_b[k][j];
            }
        }
    }

    return 0;
}

void parallel_threaded(int thread_count, int matrix_a[MS][MS], int matrix_b[MS][MS], int result[MS][MS]) {
    pthread_t treadhandles[thread_count];
    thread_data thread_data[thread_count];

    for (int i = 0; i < thread_count; ++i) {
        thread_data[i].start_row = i * (MS / thread_count);
        thread_data[i].end_row = (i + 1) * (MS / thread_count);
        for (int j = 0; j < MS; ++j) {
            for (int k = 0; k < MS; ++k) {
                thread_data[i].matrix_a[j][k] = matrix_a[j][k];
                thread_data[i].matrix_b[j][k] = matrix_b[j][k];
            }
        }
    }

    for (int i = 0; i < thread_count; ++i) {
        if (pthread_create(&treadhandles[i], NULL, worker_thread, &thread_data[i]) != 0) {
            fprintf(stderr, "create failed\n");
            exit(0);
        }
    }

    for (int i = 0; i < thread_count; ++i) {
        if (pthread_join(treadhandles[i], NULL) != 0) {
            fprintf(stderr, "join failed\n");
            exit(0);
        }
    }

    for (int i = 0; i < thread_count; ++i) {
        for (int j = thread_data[i].start_row; j < thread_data[i].end_row; ++j) {
            for (int k = 0; k < MS; ++k) {
                result[j][k] = thread_data[i].result[j][k];
            }
        }
    }
}
void parallel_detache(int thread_count, int matrix_a[MS][MS], int matrix_b[MS][MS], int result[MS][MS]) {
    pthread_t treadhandles[thread_count];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    thread_data thread_data[thread_count];

    for (int i = 0; i < thread_count; ++i) {
        thread_data[i].start_row = i * (MS / thread_count);
        thread_data[i].end_row = (i + 1) * (MS / thread_count);
        for (int j = 0; j < MS; ++j) {
            for (int k = 0; k < MS; ++k) {
                thread_data[i].matrix_a[j][k] = matrix_a[j][k];
                thread_data[i].matrix_b[j][k] = matrix_b[j][k];
            }
        }
    }
    for (int i = 0; i < thread_count; ++i) {
        if (pthread_create(&treadhandles[i], &attr, worker_thread, &thread_data[i]) != 0) {
            fprintf(stderr, "create failed\n");
            exit(0);
        }
    }

    usleep(10000);

    for (int i = 0; i < thread_count; ++i) {
        for (int j = thread_data[i].start_row; j < thread_data[i].end_row; ++j) {
            for (int k = 0; k < MS; ++k) {
                result[j][k] = thread_data[i].result[j][k];
            }
        }
    }
}

void parallel_m(int process_count, int matrix_a[MS][MS], int matrix_b[MS][MS], int result[MS][MS]) {
    pid_t process_ids[process_count];

    for (int i = 0; i < process_count; ++i) {
        int start_row = i * (MS / process_count);
        int end_row = (i + 1) * (MS / process_count);

        pid_t child_pid = fork();

        if (child_pid == -1) {
            fprintf(stderr, "fork failed\n");
            exit(0);
        }

        if (child_pid == 0) {
            for (int row = start_row; row < end_row; ++row) {
                for (int col = 0; col < MS; ++col) {
                    result[row][col] = 0;
                    for (int k = 0; k < MS; ++k) {
                        result[row][col] += matrix_a[row][k] * matrix_b[k][col];
                    }
                }
            }
            exit(1);
        } else {
            process_ids[i] = child_pid;
        }
    }

    for (int i = 0; i < process_count; ++i) {
        int status;
        waitpid(process_ids[i], &status, 0);
    }
}

int main() {

    int matrix_a[MS][MS];
    int matrix_b[MS][MS];
    int result[MS][MS];

    int student_number [7] = {1,1,9,3,1,9,1};
    int student_numberandbirthyear [10]= {2,3,8,7,5,7,5,1,9,1};
    int con1=0;
    int con2=0;
    for(int i=0; i<MS ; i++){
        for(int j=0; j<MS; j++){
            matrix_a[i][j]=student_number[con1];
            con1++;
            if(con1 == 7){
                con1=0;
            }
        }
    }
    for(int i=0; i<MS ; i++){
        for(int j=0; j<MS; j++){
            matrix_b[i][j]=student_numberandbirthyear[con2];
            con2++;
            if(con2 == 10){
                con2=0;
            }
        }
    }

    struct timeval start, end;

    gettimeofday(&start, NULL);

     for (int i = 0; i < MS; ++i) {    //  naive matrix multiplication
        for (int j = 0; j < MS; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < MS; ++k) {
                result[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }
    gettimeofday(&end, NULL);
    double timedifference = (((double)(end.tv_sec - start.tv_sec)) + ((double)(end.tv_usec - start.tv_usec))) / 1000000.0;
    printf("the naive approach time: %lf seconds\n", timedifference);

    for (int thread_count = 2; thread_count <= 4; thread_count *= 2) {
        gettimeofday(&start, NULL);
        parallel_threaded(thread_count, matrix_a, matrix_b, result);
        gettimeofday(&end, NULL);
        double timedifferencethread = (((double)(end.tv_sec - start.tv_sec)) + ((double)(end.tv_usec - start.tv_usec))) / 1000000.0;
        printf("parallel (threads=%d) time: %lf seconds\n", thread_count, timedifferencethread);
    }
    for (int process_count = 2; process_count <= 4; process_count *= 2) {
        gettimeofday(&start, NULL);
        parallel_m(process_count, matrix_a, matrix_b, result);
        gettimeofday(&end, NULL);
        double timedifferenceproc = (((double)(end.tv_sec - start.tv_sec)) + ((double)(end.tv_usec - start.tv_usec))) / 1000000.0;
        printf("parallel (processes=%d) time: %lf seconds\n", process_count, timedifferenceproc);
}
for (int thread_count = 2; thread_count <= 4; thread_count *= 2) {
                    gettimeofday(&start, NULL);
                    parallel_detache(thread_count, matrix_a, matrix_b, result);
                    gettimeofday(&end, NULL);
                    double timedifferencedeta = (((double)(end.tv_sec - start.tv_sec)) + ((double)(end.tv_usec - start.tv_usec))) / 1000000.0;
                    printf("parallel (detached threads=%d) time: %lf seconds\n", thread_count, timedifferencedeta);
                }
    return 0;
}
