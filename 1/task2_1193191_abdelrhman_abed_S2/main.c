//abdelrhman abed 1193191SS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int priority;
    int responseTime;
    int waitingTime;
    int comesBackAfter;
};


struct SchedulerQueue {
    int currenttime;
    int timeQuantum;
    struct Process* readyQueue;
    int readyQueueSize;
    struct Process* Processes;
    struct Process* copyQueue;
    struct Process* copyQueue2;
    struct Process* copyQueue3;
    struct Process* copyQueue4;
    struct Process* copyQueue5;

    int ProcessesSize;
    int copyQueueSize;
    int copyQueueSize2;
    int copyQueueSize3;
    int copyQueueSize4;
    int copyQueueSize5;
};

double turn[5];
double waiting[5];

void RoundRobin(struct SchedulerQueue* scheduler, int comesBackAfter) {
    int start = 0;
    struct Process temp;
    printf("\nRound Robin Scheduler\n");

        for (int i = 0; i < scheduler->readyQueueSize - 1; i++) {
        for (int j = 0; j < scheduler->readyQueueSize - i - 1; j++) {
            if (scheduler->readyQueue[j].arrivalTime > scheduler->readyQueue[j + 1].arrivalTime) {
                temp = scheduler->readyQueue[j];
                scheduler->readyQueue[j] = scheduler->readyQueue[j + 1];
                scheduler->readyQueue[j + 1] = temp;
            }
        }
    }

    printf("\nGantt Chart:\n");
    while (scheduler->readyQueueSize > 0) {
        struct Process currentProcess = scheduler->readyQueue[0];

        if (scheduler->currenttime < currentProcess.arrivalTime) {
            printf("| idle %d-%d ", scheduler->currenttime, currentProcess.arrivalTime);
            scheduler->currenttime = currentProcess.arrivalTime;
        }

        if (currentProcess.remainingTime >= scheduler->timeQuantum) {
            if (currentProcess.responseTime == -1) {
                scheduler->copyQueue[currentProcess.processId - 1].responseTime = scheduler->currenttime;
            }

            currentProcess.remainingTime -= scheduler->timeQuantum;
            start = scheduler->currenttime;
            scheduler->currenttime += scheduler->timeQuantum;

            int end = scheduler->currenttime;
            printf("| P%d %d-%d ", currentProcess.processId, start, end);

            if (currentProcess.responseTime == -1) {
                currentProcess.responseTime = start - currentProcess.arrivalTime;
            }

            if (currentProcess.remainingTime == 0) {
                scheduler->copyQueue[currentProcess.processId - 1].completionTime = scheduler->currenttime;
                scheduler->copyQueue[currentProcess.processId - 1].turnaroundTime = scheduler->currenttime - currentProcess.arrivalTime;

                if (comesBackAfter > 0) {
                    currentProcess.arrivalTime = scheduler->currenttime + comesBackAfter;
                    currentProcess.remainingTime = currentProcess.burstTime;
                    scheduler->readyQueue[scheduler->readyQueueSize++] = currentProcess;
                }
            } else {
                scheduler->readyQueue[scheduler->readyQueueSize++] = currentProcess;
            }
        } else {
            start = scheduler->currenttime;
            scheduler->currenttime += currentProcess.remainingTime;

            int end = scheduler->currenttime;
            printf("| P%d %d-%d ", currentProcess.processId, start, end);

            if (currentProcess.responseTime == -1) {
                currentProcess.responseTime = start - currentProcess.arrivalTime;
            }

            currentProcess.remainingTime = 0;
            scheduler->copyQueue[currentProcess.processId - 1].completionTime = scheduler->currenttime;
            scheduler->copyQueue[currentProcess.processId - 1].turnaroundTime = scheduler->currenttime - currentProcess.arrivalTime;

            if (comesBackAfter > 0) {
                currentProcess.arrivalTime = scheduler->currenttime + comesBackAfter;
                currentProcess.remainingTime = currentProcess.burstTime;
                scheduler->readyQueue[scheduler->readyQueueSize++] = currentProcess;
            }
        }

        for (int i = 0; i < scheduler->readyQueueSize - 1; i++) {
            scheduler->readyQueue[i] = scheduler->readyQueue[i + 1];
        }
        scheduler->readyQueueSize--;
    }

    for (int i = 0; i < scheduler->copyQueueSize; i++) {
    scheduler->copyQueue[i].waitingTime = scheduler->copyQueue[i].turnaroundTime - scheduler->copyQueue[i].burstTime;
    scheduler->copyQueue[i].turnaroundTime = scheduler->copyQueue[i].completionTime - scheduler->copyQueue[i].arrivalTime;
}

    printf("\n\nProcess ID\tArrival Time\tBurst Time\tPriority\t Waiting Time\tTurnaround Time\n");
    for (int i = 0; i < scheduler->ProcessesSize; i++) {
        int responseTime = scheduler->copyQueue[i].responseTime != -1 ? scheduler->copyQueue[i].responseTime : 0;
        printf("%d\t\t  %d\t\t %d\t\t %d\t\t   %d\t\t %d\t\n", scheduler->Processes[i].processId,
               scheduler->Processes[i].arrivalTime, scheduler->Processes[i].burstTime, scheduler->Processes[i].priority,
               scheduler->copyQueue[i].waitingTime, scheduler->copyQueue[i].turnaroundTime);
    }

    int sum_turnaround = 0;
    int sum_waiting = 0;

    for (int i = 0; i < scheduler->copyQueueSize; i++) {
        sum_turnaround += scheduler->copyQueue[i].turnaroundTime;
        sum_waiting += scheduler->copyQueue[i].waitingTime;
    }

    float avg_turnaround_time = (float)sum_turnaround / scheduler->copyQueueSize;
    turn[0] = avg_turnaround_time;
    float avg_waiting_time = (float)sum_waiting / scheduler->copyQueueSize;
    waiting[0] = avg_waiting_time;

    printf("\naverage Turnaround Time = %.2f\n", avg_turnaround_time);
    printf("\naverage Waiting Time = %.2f\n", avg_waiting_time);
    printf("\n******************************************\n");
}


void SJF(struct SchedulerQueue* scheduler) {
        printf("\n******************************************\n");
        printf("\nSJF Scheduler\n");


    scheduler->currenttime = 0;

    struct Process temp;

    for (int i = 0; i < scheduler->copyQueueSize2 - 1; i++) {
        for (int j = 0; j < scheduler->copyQueueSize2 - i - 1; j++) {
            if (scheduler->copyQueue2[j].arrivalTime > scheduler->copyQueue2[j + 1].arrivalTime) {
                temp = scheduler->copyQueue2[j];
                scheduler->copyQueue2[j] = scheduler->copyQueue2[j + 1];
                scheduler->copyQueue2[j + 1] = temp;
            }
        }
    }

    printf("Gantt Chart:\n");
    int ganttSize = 0;

    int completionTimes[scheduler->copyQueueSize2];
    memset(completionTimes, 0, sizeof(completionTimes));

    for (int i = 0; i < scheduler->copyQueueSize2; i++) {
        struct Process currentProcess = scheduler->copyQueue2[i];

        int start = (scheduler->currenttime > currentProcess.arrivalTime) ? scheduler->currenttime : currentProcess.arrivalTime;

        completionTimes[currentProcess.processId - 1] = start + currentProcess.burstTime;

        printf("| P%d %d-%d ", currentProcess.processId, start, completionTimes[currentProcess.processId - 1]);
        ganttSize++;

        scheduler->currenttime = completionTimes[currentProcess.processId - 1];

        if (i < scheduler->copyQueueSize2 - 1) {
            for (int k = i + 1; k < scheduler->copyQueueSize2 - 1; k++) {
                for (int l = i + 1; l < scheduler->copyQueueSize2 - 1; l++) {
                    if (scheduler->copyQueue2[l].burstTime > scheduler->copyQueue2[l + 1].burstTime) {
                        temp = scheduler->copyQueue2[l];
                        scheduler->copyQueue2[l] = scheduler->copyQueue2[l + 1];
                        scheduler->copyQueue2[l + 1] = temp;
                    }
                }
            }
        }
    }
    printf("|\n");

    for (int i = 0; i < scheduler->copyQueueSize2; i++) {
        struct Process* currentProcess = &scheduler->copyQueue2[i];
        currentProcess->completionTime = completionTimes[currentProcess->processId - 1];
        currentProcess->turnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
        currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;
    }

    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < scheduler->copyQueueSize2; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\n", scheduler->copyQueue2[i].processId, scheduler->copyQueue2[i].arrivalTime,
               scheduler->copyQueue2[i].burstTime, scheduler->copyQueue2[i].priority,
               scheduler->copyQueue2[i].waitingTime, scheduler->copyQueue2[i].turnaroundTime);
    }
    int sum_turnaround = 0;
    int sum_waiting = 0;
    for (int i = 0; i < scheduler->copyQueueSize2; i++) {
        sum_turnaround += scheduler->copyQueue2[i].turnaroundTime;
        sum_waiting += scheduler->copyQueue2[i].waitingTime;
    }
    float avg_turnaround_time = (float)sum_turnaround / scheduler->copyQueueSize2;
    float avg_waiting_time = (float)sum_waiting / scheduler->copyQueueSize2;
    turn[1] = avg_turnaround_time;
    waiting[1] = avg_waiting_time;
    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time = %.2f\n", avg_waiting_time);
    printf("\n******************************************\n");
}


void PreemptivePriorityAging(struct SchedulerQueue* scheduler) {
        printf("\n******************************************\n");
       printf("\nPreemptive Priority Scheduling with Aging\n");

    struct Process temp;
    int completedProcesses = 0;
    scheduler->currenttime = 0;
    printf("chart gantt:\n");
    while (completedProcesses < scheduler->ProcessesSize) {
        int highestPriority = 9999;
        int highestPriorityIndex = -1;

        for (int i = 0; i < scheduler->ProcessesSize; i++) {
            if (scheduler->Processes[i].arrivalTime <= scheduler->currenttime &&
                scheduler->Processes[i].priority < highestPriority &&
                scheduler->Processes[i].remainingTime > 0) {
                highestPriority = scheduler->Processes[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex == -1) {
            scheduler->currenttime++;
            continue;
        }

        struct Process* currentProcess = &scheduler->Processes[highestPriorityIndex];
        printf("| P%d %d- ", currentProcess->processId, scheduler->currenttime);

        currentProcess->remainingTime--;

        if (currentProcess->responseTime == -1) {
            currentProcess->responseTime = scheduler->currenttime - currentProcess->arrivalTime;
        }

             scheduler->currenttime++;

             printf("%d|", scheduler->currenttime);
            if (currentProcess->remainingTime == 0) {
            completedProcesses++;
            currentProcess->completionTime = scheduler->currenttime;
            currentProcess->turnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
            currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;
        }

            if ((scheduler->currenttime - currentProcess->arrivalTime) % 5 == 0) {
            currentProcess->priority--;
        }
    }

                 printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\t Waiting Time\tTurnaround Time \n");
               for (int i = 0; i < scheduler->ProcessesSize; i++) {
               printf("%d\t\t  %d\t\t %d\t\t %d\t\t %d\t\t %d\t\t\n", scheduler->Processes[i].processId,
               scheduler->Processes[i].arrivalTime, scheduler->Processes[i].burstTime,
               scheduler->Processes[i].priority, scheduler->Processes[i].waitingTime,
               scheduler->Processes[i].turnaroundTime);
    }

    int sumTurnaroundTime = 0;
    int sumWaitingTime = 0;

    for (int i = 0; i < scheduler->ProcessesSize; i++) {
        sumTurnaroundTime += scheduler->Processes[i].turnaroundTime;
        sumWaitingTime += scheduler->Processes[i].waitingTime;
    }

    float avgTurnaroundTime = (float)sumTurnaroundTime / scheduler->ProcessesSize;
    float avgWaitingTime = (float)sumWaitingTime / scheduler->ProcessesSize;

    printf("\naverage Turnaround Time = %.2f\n", avgTurnaroundTime);
    turn[5] = avgTurnaroundTime;
    printf("\naverage Waiting Time = %.2f\n", avgWaitingTime);
    waiting[5] = avgWaitingTime;

    printf("\n******************************************\n");
}

void NonPreemptivePriorityAging(struct SchedulerQueue* scheduler) {
    struct Process *currentProcess;
    int x = 0, y = 0, z = 0;
        printf("\n******************************************\n");
        printf("\nNon-Preemptive Priority Scheduler\n");

    struct Process temp;
    for (int i = 0; i < scheduler->copyQueueSize3 - 1; i++) {
        for (int j = 0; j < scheduler->copyQueueSize3 - i - 1; j++) {
            if (scheduler->copyQueue3[j].arrivalTime > scheduler->copyQueue3[j + 1].arrivalTime) {
                // Swap
                temp = scheduler->copyQueue3[j];
                       scheduler->copyQueue3[j] = scheduler->copyQueue3[j + 1];
                scheduler->copyQueue3[j + 1] = temp;
            }
        }
    }
                scheduler->currenttime = scheduler->copyQueue3[0].arrivalTime;
    int completedProcesses = 0;

    while (completedProcesses < scheduler->copyQueueSize3) {
        int highestPriority = 9999;
                   int highestPriorityIndex = -1;

        for (int i = 0; i < scheduler->copyQueueSize3; i++) {
            if (scheduler->copyQueue3[i].arrivalTime <= scheduler->currenttime &&
                      scheduler->copyQueue3[i].priority < highestPriority &&
                      scheduler->copyQueue3[i].remainingTime > 0) {
                highestPriority = scheduler->copyQueue3[i].priority;
                highestPriorityIndex = i;
            }
        }

             if (highestPriorityIndex == -1) {
            scheduler->currenttime++;
            continue;
        }

                currentProcess = &scheduler->copyQueue3[highestPriorityIndex];
        x = scheduler->currenttime;
                  y = currentProcess->arrivalTime;

        if (currentProcess->responseTime == -1) {
            scheduler->copyQueue3[highestPriorityIndex].responseTime = scheduler->currenttime;
        }

        if (z < x) {
            printf("Idle from %d to %d\n", z, x);
            scheduler->currenttime = x;
        }

        printf("| P%d %d-%d", currentProcess->processId, scheduler->currenttime, scheduler->currenttime + currentProcess->burstTime);

        scheduler->currenttime += currentProcess->burstTime;
        currentProcess->remainingTime = 0;
        completedProcesses++;
        currentProcess->completionTime = scheduler->currenttime;
        currentProcess->turnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
        currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;

        z = scheduler->currenttime;
    }

    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < scheduler->copyQueueSize3; i++) {
        printf("%d\t\t  %d\t\t %d\t\t %d\t\t %d\t\t  %d\t\t\n", scheduler->copyQueue3[i].processId, scheduler->copyQueue3[i].arrivalTime,
               scheduler->copyQueue3[i].burstTime, scheduler->copyQueue3[i].priority, scheduler->copyQueue3[i].waitingTime,
               scheduler->copyQueue3[i].turnaroundTime);
    }

    int sum = 0;
    for (int i = 0; i < scheduler->copyQueueSize3; i++) {
        sum += scheduler->copyQueue3[i].turnaroundTime;
    }

    printf("\naverage Turnaround Time = %.2f\n", (1.0) * sum / scheduler->copyQueueSize3);
    turn[2] = (1.0) * sum / scheduler->copyQueueSize3;

    sum = 0;
    for (int i = 0; i < scheduler->copyQueueSize3; i++) {
        sum += scheduler->copyQueue3[i].waitingTime;
    }

    printf("\naverage Waiting Time = %.2f\n", (1.0) * sum / scheduler->copyQueueSize3);
    waiting[2] = (1.0) * sum / scheduler->copyQueueSize3;

    sum = 0;
    for (int i = 0; i < scheduler->copyQueueSize3; i++) {
        sum += scheduler->copyQueue3[i].responseTime - scheduler->copyQueue3[i].arrivalTime;
    }

    printf("\n******************************************\n");
}

void SRTF(struct SchedulerQueue* scheduler) {
    printf("\nSRTF Scheduler\n");

    int completedProcesses = 0;
    int currenttime = 0;
    int* responseTimes = malloc(scheduler->copyQueueSize4 * sizeof(int));
    memset(responseTimes, -1, scheduler->copyQueueSize4 * sizeof(int));

    printf("\nGantt Chart:\n");

    while (completedProcesses < scheduler->copyQueueSize4) {
        int start = currenttime;
        int shortestBurstIndex = -1;
        int shortestBurstTime = INT_MAX;

        for (int i = 0; i < scheduler->copyQueueSize4; i++) {
            if (scheduler->copyQueue4[i].arrivalTime <= currenttime && scheduler->copyQueue4[i].remainingTime > 0) {
                if (scheduler->copyQueue4[i].remainingTime < shortestBurstTime) {
                    shortestBurstIndex = i;
                    shortestBurstTime = scheduler->copyQueue4[i].remainingTime;
                }
            }
        }

        if (shortestBurstIndex == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < scheduler->copyQueueSize4; i++) {
                if (scheduler->copyQueue4[i].arrivalTime > currenttime && scheduler->copyQueue4[i].arrivalTime < nextArrival) {
                    nextArrival = scheduler->copyQueue4[i].arrivalTime;
                }
            }

            if (nextArrival == INT_MAX) {
                break;
            }

            currenttime = nextArrival;
            continue;
        }

        if (responseTimes[shortestBurstIndex] == -1) {
            responseTimes[shortestBurstIndex] = currenttime - scheduler->copyQueue4[shortestBurstIndex].arrivalTime;
        }

        scheduler->copyQueue4[shortestBurstIndex].remainingTime--;
        currenttime++;

        int end = currenttime;

        printf("| P%d %d-%d ", scheduler->copyQueue4[shortestBurstIndex].processId, start, end);

        if (scheduler->copyQueue4[shortestBurstIndex].remainingTime == 0) {
            completedProcesses++;
            scheduler->copyQueue4[shortestBurstIndex].completionTime = currenttime;
            scheduler->copyQueue4[shortestBurstIndex].turnaroundTime = scheduler->copyQueue4[shortestBurstIndex].completionTime - scheduler->copyQueue4[shortestBurstIndex].arrivalTime;
            scheduler->copyQueue4[shortestBurstIndex].waitingTime = scheduler->copyQueue4[shortestBurstIndex].turnaroundTime - scheduler->copyQueue4[shortestBurstIndex].burstTime;
        }
    }

    printf("|\n\n");

    double avgTurnaroundTime = 0;
    double avgWaitingTime = 0;
    double avgResponseTime = 0;

    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < scheduler->copyQueueSize4; i++) {
        avgTurnaroundTime += scheduler->copyQueue4[i].turnaroundTime;
        avgWaitingTime += scheduler->copyQueue4[i].waitingTime;
        avgResponseTime += responseTimes[i];

        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", scheduler->Processes[i].processId, scheduler->Processes[i].arrivalTime,
               scheduler->Processes[i].burstTime, scheduler->Processes[i].priority, scheduler->copyQueue4[i].waitingTime,
               scheduler->copyQueue4[i].turnaroundTime);
    }

    avgTurnaroundTime /= scheduler->copyQueueSize4;
    avgWaitingTime /= scheduler->copyQueueSize4;
    avgResponseTime /= scheduler->copyQueueSize4;

                       printf("\naverage Turnaround Time = %.2f\n", avgTurnaroundTime);
    turn[3] = avgTurnaroundTime;

    printf("\naverage Waiting Time = %.2f\n", avgWaitingTime);
              waiting[3] = avgWaitingTime;
    printf("\n******************************************\n");

    free(responseTimes);
}


void FCFS(struct SchedulerQueue* scheduler) {
    printf("\n******************************************\n");
    printf("\nFCFS Algorithm \n");

      int currenttime = 0;
           struct Process temp;

            for (int i = 0; i < scheduler->copyQueueSize5 - 1; i++) {
            for (int j = 0; j < scheduler->copyQueueSize5 - i - 1; j++) {
            if (scheduler->copyQueue5[j].arrivalTime > scheduler->copyQueue5[j + 1].arrivalTime) {
                // Swap
                temp = scheduler->copyQueue5[j];
                scheduler->copyQueue5[j] = scheduler->copyQueue5[j + 1];
                scheduler->copyQueue5[j + 1] = temp;
            }
        }
    }

    printf("Gantt Chart:\n");

    struct GanttChartEntry {
        int processId;
        int startTime;
        int endTime;
    };

    struct GanttChartEntry ganttChart[scheduler->copyQueueSize5];
    int ganttSize = 0;

    for (int i = 0; i < scheduler->copyQueueSize5; i++) {
        struct Process* proc = &scheduler->copyQueue5[i];
        if (currenttime < proc->arrivalTime) {
            currenttime = proc->arrivalTime;
        }

        ganttChart[ganttSize].processId = proc->processId;
        ganttChart[ganttSize].startTime = currenttime;
        currenttime += proc->burstTime;
        ganttChart[ganttSize].endTime = currenttime;
        ganttSize++;

        proc->completionTime = currenttime;
           proc->turnaroundTime = proc->completionTime - proc->arrivalTime;
        proc->waitingTime = proc->turnaroundTime - proc->burstTime;

            printf("| P%d %d-%d ", proc->processId, ganttChart[ganttSize-1].startTime, ganttChart[ganttSize-1].endTime);
    }

          printf("\n");

        printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
     for (int i = 0; i < scheduler->copyQueueSize5; i++) {
         printf("%d\t\t  %d\t\t %d\t\t %d\t\t %d\t\t  %d\t\t\n", scheduler->copyQueue5[i].processId, scheduler->copyQueue5[i].arrivalTime,
                scheduler->copyQueue5[i].burstTime, scheduler->copyQueue5[i].priority, scheduler->copyQueue5[i].waitingTime, scheduler->copyQueue5[i].turnaroundTime);
    }

       int sum_turnaround = 0;
     int sum_waiting = 0;
     for (int i = 0; i < scheduler->copyQueueSize5; i++) {
         sum_turnaround += scheduler->copyQueue5[i].turnaroundTime;
         sum_waiting += scheduler->copyQueue5[i].waitingTime;
    }
     float avg_turnaround_time = (float)sum_turnaround / scheduler->copyQueueSize5;
    turn[4] = avg_turnaround_time;
    float avg_waiting_time = (float)sum_waiting / scheduler->copyQueueSize5;
    waiting[4] = avg_waiting_time;

         printf("\naverage Turnaround Time = %.2f\n", avg_turnaround_time);
        printf("\naverage Waiting Time = %.2f\n", avg_waiting_time);
      printf("\n******************************************\n");
}

int main() {
      struct SchedulerQueue scheduler;
         scheduler.currenttime = 0;
    scheduler.readyQueueSize = 0;
      scheduler.copyQueueSize = 0;
     scheduler.copyQueueSize2 = 0;
     scheduler.copyQueueSize3 = 0;
     scheduler.copyQueueSize4 = 0;
     scheduler.copyQueueSize5 = 0;
    scheduler.ProcessesSize=0;

    int numP;
    printf("enter number of processes: ");
    scanf("%d", &numP);
    while(numP<1){
        printf("number of processes must be more than 0\n");
        printf("enter number of processes: ");
        scanf("%d", &numP);
    }
    printf("enter time quantum for round robin algorithm: ");
    scanf("%d", &scheduler.timeQuantum);
    while(scheduler.timeQuantum<1){
        printf("time quantum must be more than 0\n");
        printf("enter time quantum: ");
        scanf("%d", &scheduler.timeQuantum);
    }
    printf("*********************\n");
    scheduler.Processes = malloc(sizeof(struct Process) * 10);
    scheduler.readyQueue = malloc(sizeof(struct Process) * 10);
    scheduler.copyQueue = malloc(sizeof(struct Process) * 10);
    scheduler.copyQueue2 = malloc(sizeof(struct Process) * 10);
    scheduler.copyQueue3 = malloc(sizeof(struct Process) * 10);
    scheduler.copyQueue4 = malloc(sizeof(struct Process) * 10);
    scheduler.copyQueue5 = malloc(sizeof(struct Process) * 10);

for (int i = 1; i <= numP; i++) {
    int tA, Bt, pri, comesBackAfter;
    printf("\nEnter Arrival Time for Process[%d]: ", i);
    scanf("%d", &tA);
    printf("enter burst time for process [%d]: ", i);
    scanf("%d", &Bt);
    while (Bt < 1) {
        printf("burst time must be more than 0\n");
        printf("enter burst time for process [%d]: ", i);
        scanf("%d", &Bt);
    }
    printf("enter time come back Process time[%d]: ", i);
    scanf("%d", &comesBackAfter);

    printf("enter priority for process [%d]: ", i);
    scanf("%d", &pri);

    scheduler.Processes[scheduler.ProcessesSize++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri, -1, i ,comesBackAfter};
    scheduler.readyQueue[scheduler.readyQueueSize++] = (struct Process){i, tA, Bt, Bt,  -1, -1, pri, -1, i, comesBackAfter};
    scheduler.copyQueue[scheduler.copyQueueSize++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri, -1, i, comesBackAfter};
    scheduler.copyQueue2[scheduler.copyQueueSize2++] = (struct Process){i, tA, Bt, Bt,  -1, -1, pri, -1, i,comesBackAfter};
    scheduler.copyQueue3[scheduler.copyQueueSize3++] = (struct Process){i, tA, Bt, Bt,  -1, -1, pri, -1, i,comesBackAfter};
    scheduler.copyQueue4[scheduler.copyQueueSize4++] = (struct Process){i, tA, Bt, Bt,  -1, -1, pri, -1, i,comesBackAfter};
    scheduler.copyQueue5[scheduler.copyQueueSize5++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri, -1, i,comesBackAfter};
}
    printf("\n*****************************************************************************\n");

printf("Process ID\tArrival Time\tBurst Time\tComes back after\tPriority\n");
for (int i = 0; i < scheduler.ProcessesSize; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", scheduler.Processes[i].processId, scheduler.Processes[i].arrivalTime,
           scheduler.Processes[i].burstTime, scheduler.Processes[i].comesBackAfter, scheduler.Processes[i].priority);
}



    printf("\n*****************************************************************************\n");
    while (1) {
    int choice;
    printf("\nSelect a scheduling algorithm:\n");
    printf("1. First Come First Serve (FCFS)\n");
    printf("2. Round Robin\n");
    printf("3. Shortest Remaining Time First (SRTF)\n");
    printf("4. Shortest Job First (SJF)\n");
    printf("5. Preemptive Priority\n");
    printf("6. Non-Preemptive Priority\n");
    printf("0. Exit\n");

    printf("enter your choice: \n");
    scanf("%d", &choice);
    int comesBackAfter=0;
    switch (choice) {
        case 1:
            FCFS(&scheduler);
            break;

        case 2:
             RoundRobin(&scheduler, comesBackAfter);
            break;
        case 3:
            SRTF(&scheduler);
            break;

        case 4:

             SJF(&scheduler);
            break;
        case 5:
            PreemptivePriorityAging(&scheduler);
            break;

        case 6:
            NonPreemptivePriorityAging(&scheduler);
            break;

        case 0:
            printf("good bye thank you for using my program..\n");
            exit(0);

        default:
            printf("error please enter number between [0-6].\n");
    }
}

free(scheduler.Processes);
    free(scheduler.readyQueue);
    free(scheduler.copyQueue);
    free(scheduler.copyQueue2);
    free(scheduler.copyQueue3);
    free(scheduler.copyQueue4);
    free(scheduler.copyQueue5);
    return 0;
}

