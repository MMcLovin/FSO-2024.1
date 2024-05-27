#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// process structure
typedef struct {
    int pid;
    int remaining_time;
    int burst_time;
} Process;

// cell structure
typedef struct celula {
    Process p;
    struct celula *prox;
    struct celula *ant;
} celula;

// queue's head
typedef struct {
    celula *first;
    celula *last;
    int waiting_processes;
} Queue;

// insertion in a circular doubly linked list
void enqueue(Process x, Queue **head)
{
    celula *newnode = malloc(sizeof(celula));
    newnode->p = x;
    if((*head)->first == NULL)
    {
        (*head)->first = newnode;
        (*head)->last = newnode;
        newnode->prox = newnode;
        newnode->ant = (*head)->last;
    }
    else
    {
        newnode->prox = (*head)->first;
        newnode->ant = (*head)->last;
        (*head)->last->prox = newnode;
        (*head)->last = newnode;
    }
}

// I feel like I wont be able to understand this function in the future kkkkkk
void dequeue(celula **current, Queue **head)
{
    if((*current) == (*head)->first)
    {
        // we are dequeueing the first element, so we need to update everyone that points to him like head->last and head-first
        (*head)->first = (*current)->prox;
        (*head)->last->prox = (*current)->prox;
        (*current)->prox->ant = (*current)->ant;
    }
    else
        // the thing is, I was forgetting to update the current->prox->ant, so my cells "flow" broke in the last input example from the A1.pdf (basically N > 3), since it's a particular case where the processes 2 through 9 have only 1ms of burst time left and are all being dequeued one after the other, fucking up my link from process 1 to 10
        (*current)->prox->ant = (*current)->ant;
        (*current)->ant->prox = (*current)->prox;
}

// the scheduling logic itself is ez, the troublesome part was getting the data structure right
void round_robin(Queue *head, int quantum)
{
    int burst_time = 0;
    int dynamic_quantum;

        celula *current = head->first;
        do {
            dynamic_quantum = (current->p.remaining_time < quantum) ? current->p.remaining_time : quantum;
            burst_time += dynamic_quantum;
            current->p.remaining_time -= dynamic_quantum;

            if(current->p.remaining_time == 0)
            {
                printf("%d (%d)\n", current->p.pid, burst_time);
                dequeue(&current, &head);
                head->waiting_processes--;
            }

            current = current->prox;
        } while(head->waiting_processes > 0);
}

// normal input reading from console
void read_input(int N, int quantum, Queue *head, clock_t *start)
{
    scanf("%d", &N);
    scanf("%d", &quantum);

    (*head).waiting_processes = N;

    Process p = {0, 0, 0};
    for(int i = 0; i < N; i++)
    {
        int pid, remaining_time;
        scanf("%d %d", &pid, &remaining_time);
        p.pid = pid;
        p.remaining_time = remaining_time*1000;
        enqueue(p, &head);
    }

    *start = clock();
    round_robin(head, quantum);
}

// it was boring to input the data every time, so I made a test function to debugg in codeblocks
void test_input(Queue *head, clock_t *start)
{
    int pid, remaining_time;
    int N = 10;
    int quantum = 1;
    head->waiting_processes = N;

    int input[] = { 1, 10000, 2, 1, 3, 1, 4,  1, 5, 1, 6,  1, 7, 1, 8,  1, 9, 1, 10, 60000};

    for(int i = 0; i < (N*2); i++)
    {
        pid = input[i++];
        remaining_time = input[i];
        Process p = {pid, remaining_time*1000, 0};
        enqueue(p, &head);
    }

    (*start) = clock();
    round_robin(head, quantum);

}

int main()
{
    int N, quantum;
    int pid, remaining_time;
    int burst_time = 0;
    clock_t start, end;

    Queue *head = malloc(sizeof(celula));
    head->first = NULL;
    head->last = NULL;

    // just didnt want main() to be too big
    read_input(N, quantum, head, &start);
    //test_input(head, &start);

    end = clock();
    //printf("Tempo de execucao: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}