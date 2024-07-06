#include <stdio.h>
#include <stdlib.h>
#define MAX_FRAMES 100000

// checks if the page is in memory
int lookup(int *memory, int frames, int page) {
    for(int i = 0; i < frames; i++) {
        if(memory[i] == page) {
            return 1;
        }
    }
    return 0;
}

void handle_page(int *memory, int frames, int page, int *page_faults, int *oldest_page)
{
    // if it's not in memory, replace the oldest page
    if(!lookup(memory, frames, page))
    {
        // replaces the oldest page
        memory[(*oldest_page)] = page;

        // next in FIFO and guarateens that we stay within virtual memory's range
        *oldest_page = ++(*oldest_page) % frames;

        // updates page faults
        (*page_faults)++;
    }
}

int main()
{
    int frames, pages_ref, page;
    int page_faults = 0;
    int oldest_page = 0;
    int memory[MAX_FRAMES];

    scanf("%d", &frames);
    scanf("%d", &pages_ref);

    // initializes memory array values
    for(int i = 0; i < frames; i++) memory[i] = -1;

    // reading page references
    for(int i = 0; i < pages_ref; i++)
    {
        // gets the next page referenced
        scanf("%d", &page);

        // searchs for the page, if it's not in memory, replaces the oldest page
        handle_page(memory, frames, page, &page_faults, &oldest_page);
    }

    printf("%d\n", page_faults);

    return 0;
}
