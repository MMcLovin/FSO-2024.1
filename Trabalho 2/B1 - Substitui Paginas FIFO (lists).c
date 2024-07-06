#include <stdio.h>
#include <stdlib.h>

// cell structure
typedef struct celula {
    int page;
    struct celula *prox;
    struct celula *ant;
} celula;

// queue's head
typedef struct {
    celula *first;
    celula *last;
} Queue;

// insertion in a circular doubly linked list
void enqueue(int x, Queue **head)
{
    celula *newnode = malloc(sizeof(celula));
    newnode->page = x;
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


int lookup(celula *node, int page, int frames) {
    for(int i = 0; i < frames; i++) {
        if (node->page == page) {
            return 1;
        }
        node = node->prox;
    }

    return 0;
}

int main()
{
    int frames, pages_ref, page;
    int page_faults = 0;
    int oldest_page = 0;

    scanf("%d", &frames);
    scanf("%d", &pages_ref);

    if(frames < 1 || pages_ref < 3) return 0;

    Queue *memory = malloc(sizeof(Queue));
    memory->first = NULL;
    memory->last = NULL;

    // fill the frames
    for(int i = 0; i < frames; i++)
    {
        scanf("%d", &page);
        

        if(page >= 1)
        {
            enqueue(page, &memory);
            page_faults++;
            pages_ref--;
        }
    }

    // reading remaining page references
    for(; pages_ref > 0; pages_ref--)
    {

        // gets the next page referenced
        scanf("%d", &page);

        // if it's not in memory, replace the oldest page
        if(!lookup(memory->first, page, frames))
        {
            // this guarantees that we circle thorugh the virtual memory
            memory->first->page = page;
            memory->first = memory->first->prox;
            page_faults++;
        }
    }

    printf("%d\n", page_faults);

    free(memory);

    return 0;
}
