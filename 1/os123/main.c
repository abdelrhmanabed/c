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
};
struct SchedulerQueue {
    int currentTime;
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
double turn [5];
double waiting[5];

void sortProcessesByArrivalTime(struct Process* processes, int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime)
                swap(&processes[j], &processes[j + 1]);
}
// Function to swap two processes
void swap(struct Process* a, struct Process* b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}
// Function to calculate and display metrics
void calculateAndDisplayMetrics(struct SchedulerQueue* scheduler) {
    // Display completion time, turnaround time, waiting time, and response time for each process
    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    int sum_turnaround = 0;
    int sum_waiting = 0;
    int sum_response = 0;

    for (int i = 0; i < scheduler->copyQueueSize; i++) {
        sum_turnaround += scheduler->copyQueue[i].turnaroundTime;
        sum_waiting += scheduler->copyQueue[i].waitingTime;

        scheduler->copyQueue[i].responseTime = scheduler->copyQueue[i].responseTime - scheduler->copyQueue[i].arrivalTime;
        sum_response += scheduler->copyQueue[i].responseTime;

        printf("%d\t\t  %d\t\t %d\t\t %d\t\t   %d\t\t %d\t\t\n", scheduler->Processes[i].processId,
               scheduler->Processes[i].arrivalTime, scheduler->Processes[i].burstTime,
               scheduler->Processes[i].priority, scheduler->copyQueue[i].waitingTime,
               scheduler->copyQueue[i].turnaroundTime);
    }

    float avg_turnaround_time = (float)sum_turnaround / scheduler->copyQueueSize;
    float avg_waiting_time = (float)sum_waiting / scheduler->copyQueueSize;
    float avg_response_time = (float)sum_response / scheduler->copyQueueSize;

    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time = %.2f\n", avg_waiting_time);

    // Add other metric calculations or displays if needed
}

void RoundRobin(struct SchedulerQueue* scheduler) {
    printf("\nRound Robin Scheduler\n");

    int start = 0;

    // Sort processes based on arrival time
    for (int i = 0; i < scheduler->readyQueueSize - 1; i++)
        for (int j = 0; j < scheduler->readyQueueSize - i - 1; j++)
            if (scheduler->readyQueue[j].arrivalTime > scheduler->readyQueue[j + 1].arrivalTime)
                swap(&scheduler->readyQueue[j], &scheduler->readyQueue[j + 1]);

    // Run the scheduler
    while (scheduler->readyQueueSize > 0) {
        struct Process currentProcess = scheduler->readyQueue[0];

        // Handle idle time
        if (scheduler->currentTime < currentProcess.arrivalTime) {
            printf("idle from %d to %d\n", scheduler->currentTime, currentProcess.arrivalTime);
            scheduler->currentTime = currentProcess.arrivalTime;
        }

        // Execute process
        start = scheduler->currentTime;
        int remainingTime = currentProcess.remainingTime;
        scheduler->currentTime += remainingTime < scheduler->timeQuantum ? remainingTime : scheduler->timeQuantum;

        // Display execution
        printf("Process %d executed from %d to %d\n", currentProcess.processId, start, scheduler->currentTime);

        // Update process details
        currentProcess.remainingTime -= remainingTime < scheduler->timeQuantum ? remainingTime : scheduler->timeQuantum;

        if (currentProcess.remainingTime > 0)
            scheduler->readyQueue[scheduler->readyQueueSize++] = currentProcess;
        else {
            scheduler->copyQueue[currentProcess.processId - 1].completionTime = scheduler->currentTime;
            scheduler->copyQueue[currentProcess.processId - 1].turnaroundTime =
                scheduler->currentTime - currentProcess.arrivalTime;
        }

        // Shift the ready queue
        for (int i = 0; i < scheduler->readyQueueSize - 1; i++)
            scheduler->readyQueue[i] = scheduler->readyQueue[i + 1];

        scheduler->readyQueueSize--;
    }

    // Calculate and display metrics
    calculateAndDisplayMetrics(scheduler);
}


void SJF(struct SchedulerQueue* scheduler) {
    scheduler->currentTime = 0; // Reset the current time to 0
    printf("\nSJF Scheduler\n");
    struct Process temp;

    struct Process temp1;

    // Sort the processes based on burst time using Bubble Sort
    for (int i = 0; i < scheduler->copyQueueSize2 - 1; i++) {
        for (int j = 0; j < scheduler->copyQueueSize2 - i - 1; j++) {
            if (scheduler->copyQueue2[j].burstTime > scheduler->copyQueue2[j + 1].burstTime) {
                // Swap
                temp = scheduler->copyQueue2[j];
                scheduler->copyQueue2[j] = scheduler->copyQueue2[j + 1];
                scheduler->copyQueue2[j + 1] = temp;
            }
        }
    }

    int start = 0; // Start from time 0

    for (int i = 0; i < scheduler->copyQueueSize2; i++) {
        struct Process currentProcess = scheduler->copyQueue2[i];
        scheduler->currentTime = start;
        int end = scheduler->currentTime + currentProcess.burstTime;

        // Calculate and print the response time
        printf("Process %d executed for %d units (start at %d end at %d) \n",
               currentProcess.processId, currentProcess.burstTime, start, end);

        scheduler->copyQueue2[i].completionTime = end;
        scheduler->copyQueue2[i].waitingTime = start ;
        scheduler->copyQueue2[i].turnaroundTime = scheduler->copyQueue2[i].waitingTime +scheduler->copyQueue2[i].burstTime;

        start = end;
    }
// Sort the processes based on id using Bubble Sort
    for (int i = 0; i < scheduler->copyQueueSize2 - 1; i++) {
        for (int j = 0; j < scheduler->copyQueueSize2 - i - 1; j++) {
            if (scheduler->copyQueue2[j].processId > scheduler->copyQueue2[j + 1].processId) {
                // Swap
                temp = scheduler->copyQueue2[j];
                scheduler->copyQueue2[j] = scheduler->copyQueue2[j + 1];
                scheduler->copyQueue2[j + 1] = temp;
            }
        }
    }
    // Display completion time, turnaround time, and waiting time for each process
    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\t Waiting Time\tTurnaround Time   \n");
    for (int i = 0; i < scheduler->copyQueueSize5; i++) {
        printf("%d\t\t  %d\t\t %d\t\t %d\t\t %d\t\t %d\t\t  \n", scheduler->copyQueue2[i].processId, scheduler->copyQueue2[i].arrivalTime,
               scheduler->copyQueue2[i].burstTime, scheduler->copyQueue2[i].priority,
               scheduler->copyQueue2[i].waitingTime, scheduler->copyQueue2[i].turnaroundTime);
    }


    int sum_turnaround_time = 0;
    int sum_waiting_time = 0;

    for (int i = 0; i < scheduler->copyQueueSize2; i++) {
        sum_turnaround_time += scheduler->copyQueue2[i].turnaroundTime;
        sum_waiting_time += scheduler->copyQueue2[i].waitingTime;
    }

    float avg_turnaround_time = (float)sum_turnaround_time / scheduler->copyQueueSize2;
    turn[1]=avg_turnaround_time;
    float avg_waiting_time = (float)sum_waiting_time / scheduler->copyQueueSize2;
    waiting[1]=avg_waiting_time;

    printf("Average Turnaround Time = %.2f\n",avg_turnaround_time);
    printf("Average Waiting Time = %.2f\n", avg_waiting_time);
    printf("\n******************************************\n");
}



void executeProcess(struct Process* process, int start, int end) {
    printf("Process %d executed from %d to %d\n", process->processId, start, end);
}

void updateProcessDetails(struct Process* process, int currentTime, int* sumResponse, int* sumTurnaround, int* sumWaiting) {
    process->completionTime = currentTime + process->burstTime;
    process->turnaroundTime = process->completionTime - process->arrivalTime;
    process->waitingTime = process->turnaroundTime - process->burstTime;
    process->responseTime = currentTime - process->arrivalTime;

    *sumResponse += process->responseTime;
    *sumTurnaround += process->turnaroundTime;
    *sumWaiting += process->waitingTime;
}

void preemptivePriorityAging(struct SchedulerQueue* scheduler) {
    printf("\nPreemptive Priority Scheduling with Aging\n");

    int completedProcesses = 0;
    scheduler->currentTime = 0;

    while (completedProcesses < scheduler->ProcessesSize) {
        int highestPriority = 9999;
        int highestPriorityIndex = -1;

        for (int i = 0; i < scheduler->ProcessesSize; i++) {
            if (scheduler->Processes[i].arrivalTime <= scheduler->currentTime &&
                scheduler->Processes[i].priority < highestPriority &&
                scheduler->Processes[i].remainingTime > 0) {
                highestPriority = scheduler->Processes[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex == -1) {
            scheduler->currentTime++;
            continue;
        }

        struct Process* currentProcess = &scheduler->Processes[highestPriorityIndex];
        executeProcess(currentProcess, scheduler->currentTime, scheduler->currentTime + 1);
        currentProcess->remainingTime--;

        if (currentProcess->responseTime == -1) {
            currentProcess->responseTime = scheduler->currentTime - currentProcess->arrivalTime;
        }

        scheduler->currentTime++;

        if (currentProcess->remainingTime == 0) {
            completedProcesses++;
            updateProcessDetails(currentProcess, scheduler->currentTime, &sumResponse, &sumTurnaround, &sumWaiting);
        }

        if ((scheduler->currentTime - currentProcess->arrivalTime) % 5 == 0) {
            currentProcess->priority--;
        }
    }

    displayProcessInformation(scheduler->Processes, scheduler->ProcessesSize);
    calculateAndDisplayAverages(sumTurnaround, sumWaiting, 4);
}

void nonPreemptivePriorityAging(struct SchedulerQueue* scheduler) {
    printf("\nNon-Preemptive Priority Scheduling with Aging\n");

    sortProcessesByArrivalTime(scheduler->copyQueue3, scheduler->copyQueueSize3);
    scheduler->currentTime = scheduler->copyQueue3[0].arrivalTime;
    int completedProcesses = 0;

    while (completedProcesses < scheduler->copyQueueSize3) {
        int highestPriority = 9999;
        int highestPriorityIndex = -1;

        for (int i = 0; i < scheduler->copyQueueSize3; i++) {
            if (scheduler->copyQueue3[i].arrivalTime <= scheduler->currentTime &&
                scheduler->copyQueue3[i].priority < highestPriority &&
                scheduler->copyQueue3[i].remainingTime > 0) {
                highestPriority = scheduler->copyQueue3[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex == -1) {
            scheduler->currentTime++;
            continue;
        }

        struct Process currentProcess = scheduler->copyQueue3[highestPriorityIndex];
        scheduler->currentTime += currentProcess.remainingTime;
        completedProcesses++;

        updateProcessDetails(&scheduler->copyQueue3[highestPriorityIndex], scheduler->currentTime, &sumResponse, &sumTurnaround, &sumWaiting);

        if ((scheduler->currentTime - currentProcess.arrivalTime) >= 5) {
            scheduler->copyQueue3[highestPriorityIndex].priority--;
        }

        executeProcess(&currentProcess, scheduler->currentTime - currentProcess.remainingTime, scheduler->currentTime);
    }

    displayProcessInformation(scheduler->Processes, scheduler->ProcessesSize);
    calculateAndDisplayAverages(sumTurnaround, sumWaiting, 5);
}

void SRTF(struct SchedulerQueue* scheduler) {
    printf("\nSRTF Scheduler\n");

    int completedProcesses = 0, currentTime = 0;
    int* responseTimes = malloc(scheduler->copyQueueSize4 * sizeof(int));
    memset(responseTimes, -1, scheduler->copyQueueSize4 * sizeof(int));

    while (completedProcesses < scheduler->copyQueueSize4) {
        int shortestBurstIndex = -1, shortestBurstTime = INT_MAX;

        for (int i = 0; i < scheduler->copyQueueSize4; i++) {
            if (scheduler->copyQueue4[i].arrivalTime <= currentTime &&
                scheduler->copyQueue4[i].remainingTime > 0 &&
                scheduler->copyQueue4[i].remainingTime < shortestBurstTime) {
                shortestBurstIndex = i;
                shortestBurstTime = scheduler->copyQueue4[i].remainingTime;
            }
        }

        if (shortestBurstIndex == -1) {
            printf(" idle from %d to %d\n", currentTime, currentTime + 1);
            currentTime++;
            continue;
        }

        if (responseTimes[shortestBurstIndex] == -1)
            responseTimes[shortestBurstIndex] = currentTime - scheduler->copyQueue4[shortestBurstIndex].arrivalTime;

        scheduler->copyQueue4[shortestBurstIndex].remainingTime--;
        currentTime++;

        executeProcess(&scheduler->copyQueue4[shortestBurstIndex], currentTime - 1, currentTime);

        if (scheduler->copyQueue4[shortestBurstIndex].remainingTime == 0) {
            completedProcesses++;
            struct Process* currentProcess = &scheduler->copyQueue4[shortestBurstIndex];
            currentProcess->completionTime = currentTime;
            currentProcess->turnaroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
            currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;
        }
    }

    displayProcessInformation(scheduler->Processes, scheduler->ProcessesSize);
    calculateAndDisplayAverages(sumTurnaround, sumWaiting, 3);
    free(responseTimes);
}

void FCFS(struct SchedulerQueue* scheduler) {
    printf("\nFCFS Algorithm\n");

    int currentTime = 0, sumResponse = 0, sumTurnaround = 0, sumWaiting = 0;
    sortProcessesByArrivalTime(scheduler->copyQueue5, scheduler->copyQueueSize5);

    for (int i = 0; i < scheduler->copyQueueSize5; i++) {
        if (scheduler->copyQueue5[i].arrivalTime > currentTime) {
            printf("idle from %d to %d\n", currentTime, scheduler->copyQueue5[i].arrivalTime);
            currentTime = scheduler->copyQueue5[i].arrivalTime;
        }

        executeProcess(&scheduler->copyQueue5[i], currentTime, currentTime + scheduler->copyQueue5[i].burstTime);

        updateProcessDetails(&scheduler->copyQueue5[i], currentTime, &sumResponse, &sumTurnaround, &sumWaiting);

        currentTime = scheduler->copyQueue5[i].completionTime;
    }

    displayProcessInformation(scheduler->copyQueue5, scheduler->copyQueueSize5);
    calculateAndDisplayAverages(sumTurnaround, sumWaiting, 4);
}


int main() {
    struct SchedulerQueue scheduler;
    scheduler.currentTime = 0;
    scheduler.readyQueueSize = 0;
    scheduler.copyQueueSize = 0;
    scheduler.copyQueueSize2 = 0;
    scheduler.copyQueueSize3 = 0;
    scheduler.copyQueueSize4 = 0;
    scheduler.copyQueueSize5 = 0;
    scheduler.ProcessesSize=0;


    // Add processes to the scheduler
    int numP;
    printf("Enter number of Processes: ");
    scanf("%d", &numP);
    while(numP<1){
        printf("Number of Processes must be more than 0!!!\n");
        printf("Enter number of Processes: ");
        scanf("%d", &numP);
    }
    printf("Enter Time Quantum For RoundRobin Algorithm: ");
    scanf("%d", &scheduler.timeQuantum);
    while(scheduler.timeQuantum<1){
        printf("Time Quantum must be more than 0!!!\n");
        printf("Enter Time Quantum: ");
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
        int tA, Bt, pri;
        printf("\nEnter Arrival Time for Process[%d]: ", i);
        scanf("%d", &tA);
        printf("Enter Burst Time for Process [%d]: ", i);
        scanf("%d", &Bt);
        while(Bt<1){
            printf("Burst Time must be more than 0!!!\n");
            printf("Enter Burst Time for Process [%d]: ", i);
            scanf("%d", &Bt);
        }
        printf("Enter Priority for Process [%d]: ", i);
        scanf("%d", &pri);

        scheduler.Processes[scheduler.ProcessesSize++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};
        scheduler.readyQueue[scheduler.readyQueueSize++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};
        scheduler.copyQueue[scheduler.copyQueueSize++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};
        scheduler.copyQueue2[scheduler.copyQueueSize2++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};
        scheduler.copyQueue3[scheduler.copyQueueSize3++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};
        scheduler.copyQueue4[scheduler.copyQueueSize4++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};
        scheduler.copyQueue5[scheduler.copyQueueSize5++] = (struct Process){i, tA, Bt, Bt, -1, -1, pri,-1};

    }

    printf("\n*****************************************************************************\n");


    // Print the process details
    printf("Process ID\tArrival Time\tBurst Time\tPriority\t\n");
    for (int i = 0; i < numP; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\n", scheduler.readyQueue[i].processId, scheduler.readyQueue[i].arrivalTime,
               scheduler.readyQueue[i].burstTime, scheduler.readyQueue[i].priority);
    }
    printf("\n*****************************************************************************\n");

    FCFS(&scheduler);
    SJF(&scheduler);
    SRTF(&scheduler);
    RoundRobin(&scheduler);
    PreemptivePriorityAging(&scheduler);
    NonPreemptivePriorityAging(&scheduler);



    // Find the best Algorithm for Turnaround time :
    int BestTurn=turn[0];
    int algorithm=-1;
    for (int i = 0; i <= 4; i++) {
        if (turn[i] <= BestTurn) {
            BestTurn = turn[i];
            algorithm=i;
        }
    }
    printf("*****************************************************************************************\n");
    if(algorithm==0){
        printf("The Best Algorithm For Turnarround Time is RoundRobin with average turnarround time = %0.2f\n",turn[0]);

    }
    if(algorithm==1){
        printf("The Best Algorithm For Turnarround Time is SJF with average turnarround time = %0.2f\n",turn[1]);

    }
    if(algorithm==2){
        printf("The Best Algorithm For Turnarround Time is Priority Preemptive with average turnarround time = %0.2f\n",turn[2]);

    }
    if(algorithm==3){
        printf("The Best Algorithm For Turnarround Time is SRTF with average turnarround time = %0.2f\n",turn[3]);

    }
    if(algorithm==4){
        printf("The Best Algorithm For Turnarround Time is FCFS with average turnarround time = %0.2f\n",turn[4]);

    }
    int BestWait=waiting[0];
    int algorithm2=-1;

    for (int i = 0; i <= 4; i++) {
        if (waiting[i] <= BestWait) {
            BestWait = waiting[i];
            algorithm2=i;
        }
    }
    if(algorithm2==0){
        printf("The Best Algorithm For Waiting Time is RoundRobin with average turnarround time = %0.2f\n",waiting[0]);

    }
    if(algorithm2==1){
        printf("The Best Algorithm For Waiting Time is SJF with average turnarround time = %0.2f\n",waiting[1]);

    }
    if(algorithm2==2){
        printf("The Best Algorithm For Waiting Time is Priority Preemptive with average turnarround time = %0.2f\n",waiting[2]);

    }
    if(algorithm2==3){
        printf("The Best Algorithm For Waiting Time is SRTF with average turnarround time = %0.2f\n",waiting[3]);

    }
    if(algorithm2==4){
        printf("The Best Algorithm For Waiting Time is FCFS with average turnarround time = %0.2f\n",waiting[4]);

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
