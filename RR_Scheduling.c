// EG/2020/3986 Jayasinghe D.M.S.N.


#include <stdio.h>
#include <stdbool.h>

// Define the structure for a process
struct Process {
    int pid;           // Process ID
    int arrival;       // Arrival time of the process
    int burst;         // Burst time of the process
    int remaining;     // Remaining time to complete the process
    int waiting;       // Waiting time of the process
    int turnaround;    // Turnaround time of the process
};

// Function to calculate waiting time for each process using Round Robin scheduling
void roundRobinScheduling(struct Process proc[], int n, int quantum) {
    int currentTime = 0;        // Current time
    int completed = 0;           // Number of completed processes
    bool isCompleted[n];         // Array to keep track of completed processes
    int queue[100];              // Queue to store process indices
    int front = 0, rear = 0;     // Front and rear indices of the queue

    // Initialize isCompleted array and remaining times
    for (int i = 0; i < n; i++) {
        isCompleted[i] = false;
        proc[i].remaining = proc[i].burst;
        proc[i].waiting = 0;
    }

    // Add first process to the queue
    queue[rear++] = 0;

    // Loop until all processes are completed
    while (completed != n) {
        int idx = queue[front++];  // Get the index of the current process

        // If remaining time is less than or equal to quantum, execute the process
        if (proc[idx].remaining <= quantum) {
            currentTime += proc[idx].remaining;  // Update current time
            proc[idx].remaining = 0;             // Set remaining time to 0
            isCompleted[idx] = true;             // Mark process as completed
            completed++;                         // Increment completed processes count
            // Calculate turnaround and waiting time for the process
            proc[idx].turnaround = currentTime - proc[idx].arrival;
            proc[idx].waiting = proc[idx].turnaround - proc[idx].burst;

            // Add processes to the queue which have arrived and not completed yet
            for (int i = 0; i < n; i++) {
                if (!isCompleted[i] && proc[i].arrival <= currentTime && i != idx) {
                    bool inQueue = false;
                    for (int j = front; j < rear; j++) {
                        if (queue[j] == i) {
                            inQueue = true;
                            break;
                        }
                    }
                    if (!inQueue) {
                        queue[rear++] = i;  // Add process to the queue
                    }
                }
            }
        } else {
            // If remaining time is more than quantum, execute the process for quantum time
            currentTime += quantum;  // Update current time
            proc[idx].remaining -= quantum;  // Decrease remaining time of the process

            // Add processes to the queue which have arrived and not completed yet
            for (int i = 0; i < n; i++) {
                if (!isCompleted[i] && proc[i].arrival <= currentTime && i != idx) {
                    bool inQueue = false;
                    for (int j = front; j < rear; j++) {
                        if (queue[j] == i) {
                            inQueue = true;
                            break;
                        }
                    }
                    if (!inQueue) {
                        queue[rear++] = i;  // Add process to the queue
                    }
                }
            }
            queue[rear++] = idx;  // Add current process back to the queue
        }

        // If the queue is empty, add a process which has arrived and not completed yet
        if (front == rear) {
            for (int i = 0; i < n; i++) {
                if (!isCompleted[i]) {
                    queue[rear++] = i;  // Add process to the queue
                    break;
                }
            }
        }
    }
}

// Function to calculate average waiting time of processes
float calculateAverageWaitingTime(struct Process proc[], int n) {
    int totalWaitingTime = 0;

    // Calculate total waiting time of all processes
    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waiting;
    }

    // Return average waiting time
    return (float)totalWaitingTime / n;
}

int main() {
    // Define processes
    struct Process proc[] = {
        {1, 0, 10},
        {2, 6, 8},
        {3, 7, 4},
        {4, 9, 5}
    };
    int n = sizeof(proc) / sizeof(proc[0]);  // Number of processes
    int quantum = 2;  // Quantum for Round Robin scheduling

    // Perform Round Robin scheduling
    roundRobinScheduling(proc, n, quantum);

    // Calculate average waiting time
    float averageWaitingTime = calculateAverageWaitingTime(proc, n);

    // Output results
    printf("----RR Scheduling----\n");
    printf("\n");
    printf("Process\t\tArrival Time\tBurst Time\tTurnaround Time\t\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", proc[i].pid, proc[i].arrival, proc[i].burst, proc[i].turnaround, proc[i].waiting);
    }
    printf("\n");
    printf("Average Waiting Time: %.2f\n", averageWaitingTime);
    printf("\n");

    return 0;
}
