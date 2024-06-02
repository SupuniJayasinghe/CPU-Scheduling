// EG/2020/3986 Jayasinghe D.M.S.N.

#include <stdio.h>

// Define the Process structure
typedef struct {
    int arrival_time;       // Arrival time of the process
    int burst_time;         // Burst time required by the process
    int waiting_time;       // Waiting time of the process
    int turnaround_time;    // Turnaround time of the process
} Process;

// Function to perform First Come First Serve (FCFS) scheduling
void fcfs(Process processes[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        // If current time is less than arrival time of the process, update current time
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        // Calculate waiting time and update current time
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        current_time += processes[i].burst_time;
        // Calculate turnaround time
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

// Function to calculate average waiting time of processes
double calculate_average_waiting_time(Process processes[], int n) {
    int total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
    }
    return (double)total_waiting_time / n;
}

int main() {
    Process processes[] = {{0, 10, 0, 0}, {6, 8, 0, 0}, {7, 4, 0, 0}, {9, 5, 0, 0}};
    int n = sizeof(processes) / sizeof(processes[0]);

    // Perform FCFS scheduling
    fcfs(processes, n);
    // Calculate average waiting time
    double avg_waiting_time_fcfs = calculate_average_waiting_time(processes, n);

    // Output results
    printf("\n----FCFS Scheduling----\n");
    printf("\n");
    printf("Process\t\tArrival Time\tBurst Time\tTurnaround Time\t\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", i + 1, processes[i].arrival_time, processes[i].burst_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    printf("\nAverage Waiting Time (FCFS): %.2f\n", avg_waiting_time_fcfs);
    printf("\n");

    return 0;
}
