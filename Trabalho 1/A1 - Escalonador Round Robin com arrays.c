#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// process structure
typedef struct {
    int pid;                    // process ID
    int burst_time;             // time taken to execute
    int remaining_time;         // remaining time to execute
} Process;

// round robin algorithm
void round_robin(Process *p_vet, int N, int quantum)
{
    int executed = 0;
    int burst_time = 0;

    while(executed != N)
    {
        // I tried using '% N' for circling through p_vet, but since division is too costly, 'while' does a waaay better job
        for (int i = 0; i < N; i++)
        {
            if (p_vet[i].remaining_time > 0)
            {          
                // this was also a gpt optimization, apparently, using the ternary operator is faster than if/else for deciding the dynamic quantum  
                int dynamic_quantum = (p_vet[i].remaining_time < quantum) ? p_vet[i].remaining_time : quantum;
                p_vet[i].remaining_time -= dynamic_quantum;
                burst_time += quantum;

                if(p_vet[i].remaining_time == 0)
                {
                    executed++;
                    p_vet[i].burst_time = burst_time;
                    printf("%d (%d)\n", p_vet[i].pid, p_vet[i].burst_time);
                }
            }
        }
    }
}

int main()
{
    int N, quantum, pid, remaining_time;
    clock_t end_time, start_time;

    scanf("%d", &N);
    scanf("%d", &quantum);

    Process *p_vet = malloc(N * sizeof(Process));
    Process p = {0, 0, 0};
    
    for(int i = 0; i < N; i++)
    {
        scanf("%d %d", &pid, &remaining_time);
        p.pid = pid;
        p.remaining_time = remaining_time*1000;
        p_vet[i] = p;
    }
    start_time = clock();
    round_robin(p_vet, N, quantum);
    end_time = clock();
    
    float cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU Time Used: %f seconds\n", cpu_time_used);

    return 0;
}