// EG/2020/3986 Jayasinghe D.M.S.N.

#include <stdio.h>
#include <limits.h>

// Define the Process struct
typedef struct {
    int arrival_time;       // Arrival time of the process
    int burst_time;         // Burst time required by the process
    int waiting_time;       // Waiting time of the process
    int turnaround_time;    // Turnaround time of the process
} Process;

// Function to perform Shortest Job First (SJF) scheduling
void sjf(Process processes[], int n) {
    int complete = 0, t = 0, min_burst = INT_MAX;
    int shortest = 0, finish_time;
    int waiting_time[n], turnaround_time[n], burst_remaining[n];

    // Initialize burst_remaining array with burst times of processes
    for (int i = 0; i < n; i++)
        burst_remaining[i] = processes[i].burst_time;
    
    // Loop until all processes are completed
    while (complete != n) {
        // Find the process with the shortest remaining burst time
        for (int j = 0; j < n; j++) {
            if ((processes[j].arrival_time <= t) && (burst_remaining[j] < min_burst) && burst_remaining[j] > 0) {
                min_burst = burst_remaining[j];
                shortest = j;
            }
        }
        
        // Execute the selected process for one time unit
        burst_remaining[shortest]--;
        min_burst = burst_remaining[shortest];
        if (min_burst == 0)
            min_burst = INT_MAX;

        // If the process is completed, calculate waiting and turnaround times
        if (burst_remaining[shortest] == 0) {
            complete++;
            finish_time = t + 1;
            waiting_time[shortest] = finish_time - processes[shortest].burst_time - processes[shortest].arrival_time;
            if (waiting_time[shortest] < 0)
                waiting_time[shortest] = 0;
        }
        t++;
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
    }

    // Output results
    printf("----SJF Scheduling----\n");
    printf("\n");
    printf("Process\t\tArrival Time\tBurst Time\tTurnaround Time\t\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", i + 1, processes[i].arrival_time, processes[i].burst_time, turnaround_time[i], waiting_time[i]);
    }
    printf("\n");

    // Calculate average waiting time
    double avg_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += waiting_time[i];
    }
    avg_waiting_time /= n;
    printf("Average Waiting Time (SJF): %.2f\n\n", avg_waiting_time);
}

int main() {
    // Define processes
    Process processes[] = {{0, 10, 0, 0}, {6, 8, 0, 0}, {7, 4, 0, 0}, {9, 5, 0, 0}};
    int n = sizeof(processes) / sizeof(processes[0]);

    // Perform SJF scheduling
    sjf(processes, n);

    return 0;
}
