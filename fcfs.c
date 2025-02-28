#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int at[], int wt[]) {
    int service_time[n];
    service_time[0] = at[0];
    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i - 1] + bt[i - 1];
        wt[i] = service_time[i] - at[i];
        if (wt[i] < 0)
            wt[i] = 0;
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findavgTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, at, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("Processes Burst time Arrival time Waiting time Turn around time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], at[i], wt[i], tat[i]);
    }

    float s = (float)total_wt / (float)n;
    float t = (float)total_tat / (float)n;
    printf("Average waiting time = %f\n", s);
    printf("Average turn around time = %f\n", t);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], arrival_time[n];

    printf("Enter arrival and burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Arrival time for process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        processes[i] = i + 1; 
    }

    findavgTime(processes, n, burst_time, arrival_time);

    return 0;
}
