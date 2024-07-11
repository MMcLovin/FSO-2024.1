#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// cell structure
typedef struct celula {
    int page;
    int last_accessed;
    struct celula *prox;
} celula;

// queue's head
typedef struct {
    celula *first;
    celula *last;
    time_t least_used_time;
} Queue;

// insertion in a linked list
void enqueue(int x, Queue **head, int count)
{
    celula *newnode = malloc(sizeof(celula));
    newnode->page = x;
    newnode->last_accessed = count;
    newnode->prox = NULL;

    // the list is empty
    if((*head)->first == NULL)
    {
        (*head)->last = newnode;
        (*head)->first = newnode;
        (*head)->least_used_time = newnode->last_accessed;
    }
    else
    {
        (*head)->last->prox = newnode;
        (*head)->last = newnode;
    }
}


int lookup(celula *node, int page, int frames, int count) {
    for(; node != NULL; node = node->prox)
    {
        if (node->page == page) {
            node->last_accessed = count;
            return 1;
        }
    }
    return 0;
}


void update_oldest_time(Queue **memory) {
    celula *aux = (*memory)->first;

    int menor = aux->last_accessed;

    while (aux != NULL)
    {
        if (aux->last_accessed <= menor)
        {
            (*memory)->least_used_time = aux->last_accessed;
            menor = aux->last_accessed;
        }

        aux = aux->prox;
    }
}

int handle_page(Queue **memory, int page, int frames, int count) {
    if(!lookup((*memory)->first, page, frames, count))
    {
        // the page referenced is not in memory, we have to search for the least used one and replace it

        // aux to help us manipulate the pages
        celula *aux = (*memory)->first;

        // searching for the oldest page
        while (aux != NULL)
        {
            // found the oldest page
            if (aux->last_accessed == (*memory)->least_used_time)
            {
                aux->page = page;
                aux->last_accessed = count;
                update_oldest_time(memory);

                break;
            }

            // we are literally changing aux, if we were to change a value in aux we would have to change it in the list, thus making a mess
            aux = aux->prox;
        }
        return 1;
    }
    update_oldest_time(memory);
    return 0;
}

int main()
{
    int frames, pages_ref, page;
    int page_faults = 0;

    scanf("%d", &frames);
    scanf("%d", &pages_ref);

    if(frames < 1 || pages_ref < 3) return 0;

    Queue *memory = malloc(sizeof(Queue));
    memory->first = NULL;
    memory->least_used_time = -1;

    for(int i = 0; i < frames; i++)
    {
        scanf("%d", &page);
        enqueue(page, &memory, i);
        page_faults++;
    }
    // (*memory)->first
    // (*memory)->first->prox
    // (*memory)->first->prox->prox
    // (*memory)->first->prox->prox->prox
    // reading page references
    for(int i = frames; i < pages_ref; i++)
    {
        // gets the next page referenced
        scanf("%d", &page);

        page_faults += handle_page(&memory, page, frames, i);
    }

    printf("%d\n", page_faults);

    free(memory);

    return 0;
}
