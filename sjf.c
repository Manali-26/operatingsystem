#include <stdio.h>

typedef struct {
    int processID;
    int burstTime;
    int arrivalTime;
} Process;

void findCompletionTime(Process proc[], int n, int ct[]) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < proc[i].arrivalTime) {
            currentTime = proc[i].arrivalTime;
        }
        currentTime += proc[i].burstTime;
        ct[i] = currentTime;
    }
}

void findWaitingTime(Process proc[], int n, int wt[], int ct[]) {
    for (int i = 0; i < n; i++) {
        wt[i] = ct[i] - proc[i].burstTime - proc[i].arrivalTime;
        if (wt[i] < 0) {
            wt[i] = 0;
        }
    }
}

void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].burstTime + wt[i];
    }
}

void findavgTime(Process proc[], int n) {
    int wt[n], tat[n], ct[n], total_wt = 0, total_tat = 0;

    findCompletionTime(proc, n, ct);
    findWaitingTime(proc, n, wt, ct);
    findTurnAroundTime(proc, n, wt, tat);

    printf("Processes  Burst Time  Arrival Time  Completion Time  Waiting Time  Turnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].processID, proc[i].burstTime, proc[i].arrivalTime, ct[i], wt[i], tat[i]);
    }

    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("Average waiting time = %.2f\n", avg_wt);
    printf("Average turnaround time = %.2f\n", avg_tat);
}

int compareByBurstTime(const void *a, const void *b) {
    Process *procA = (Process *)a;
    Process *procB = (Process *)b;
    return (procA->burstTime - procB->burstTime);
}

void sortProcessesByArrivalAndBurstTime(Process proc[], int n) {
    int currentTime = 0, completed = 0;
    while (completed < n) {
        int minIdx = -1;
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].burstTime > 0) {
                if (minIdx == -1 || proc[i].burstTime < proc[minIdx].burstTime) {
                    minIdx = i;
                }
            }
        }
        if (minIdx != -1) {
            currentTime += proc[minIdx].burstTime;
            proc[minIdx].burstTime = 0;
            proc[minIdx].arrivalTime = currentTime;
            completed++;
        } else {
            currentTime++;
        }
    }
    qsort(proc, n, sizeof(Process), compareByBurstTime);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n];
    printf("Enter process IDs, arrival times, and burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process ID[%d]: ", i + 1);
        scanf("%d", &proc[i].processID);
        printf("Arrival Time[%d]: ", i + 1);
        scanf("%d", &proc[i].arrivalTime);
        printf("Burst Time[%d]: ", i + 1);
        scanf("%d", &proc[i].burstTime);
    }

    sortProcessesByArrivalAndBurstTime(proc, n);
    findavgTime(proc, n);
    return 0;
}
