#include<stdio.h>
#include<stdlib.h>
#include<string.h>
print("hello");
#define NUM_PROCESSES 4    // Number of processes
#define NUM_PAGES 4        // Number of pages per process
#define RAM_SIZE 16        // Size of RAM (16 slots, 8 frames)
#define PAGE_SIZE 2        // Number of slots per page (2 slots)
#define MAX_LINE_LENGTH 100 // Maximum length for a line in the input file
#define IN_VIRTUAL_MEMORY 99 // Indicator that a page is in virtual memory

struct memory {
    int process_id;
    int page_num;
    int last_accessed;
};

int main() {
    /* Start of garbage */
    FILE *input_file = fopen("in.txt", "r");
    if (input_file == NULL) {
        printf("Error: Could not open file in.txt\n");
        return 1;
    }

    int process_ids[100];  // Assuming the input file will have at most 100 process IDs
    int index = 0;         // To keep track of how many integers we've read

    while (fscanf(input_file, "%d", &process_ids[index]) == 1) {
        index++;
    }

    fclose(input_file);

    printf("Process IDs read from file:\n");
    for (int i = 0; i < index; i++) {
        printf("%d ", process_ids[i]);
    }
    printf("\n");

    /* End of garbage */

    /* Start initialize RAM */
    struct memory *RAM[RAM_SIZE];
    // Initialize RAM with NULL (indicating empty slots)
    for (int i = 0; i < RAM_SIZE; i++) {
        RAM[i] = NULL;
    }

    /* End initialize RAM */

    /* Start initialize every page in virtual memory */
    int page_table[NUM_PROCESSES][NUM_PAGES];
    // Set all page table entries to 99 (indicating virtual memory)
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_PAGES; j++) {
            page_table[i][j] = IN_VIRTUAL_MEMORY;
        }
    }

    // Print the page tables for debugging
    printf("Page tables initialized to virtual memory:\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < NUM_PAGES; j++) {
            printf("%d ", page_table[i][j]);
        }
        printf("\n");
    }

    /* End initialize every page in virtual memory */

    /* Start simulate page accesses */
    int counter_p0 = 0, counter_p1 = 0, counter_p2 = 0, counter_p3 = 0; // Counters for each process
    int time = 0; // Time step for tracking the last accessed time

    for (int i = 0; i < index; i++) {
        int pid = process_ids[i];
        int start_frame = -1;

        // Inline logic to find two consecutive empty frames
        for (int j = 0; j < RAM_SIZE - 1; j++) {
            if (RAM[j] == NULL && RAM[j + 1] == NULL) {
                start_frame = j;
                break;
            }
        }

        if (start_frame != -1) { // Only proceed if two consecutive frames are found
            if (pid == 0) {
                if (RAM[start_frame] == NULL && RAM[start_frame + 1] == NULL) {
                    RAM[start_frame] = (struct memory*)malloc(sizeof(struct memory));
                    RAM[start_frame + 1] = (struct memory*)malloc(sizeof(struct memory));

                    RAM[start_frame]->process_id = pid;
                    RAM[start_frame]->page_num = counter_p0 % NUM_PAGES;
                    RAM[start_frame]->last_accessed = time;

                    RAM[start_frame + 1]->process_id = pid;  // Duplicate in the next frame
                    RAM[start_frame + 1]->page_num = counter_p0 % NUM_PAGES;
                    RAM[start_frame + 1]->last_accessed = time;

                    page_table[pid][counter_p0 % NUM_PAGES] = RAM[start_frame]->page_num;

                    printf("RAM[%d] and RAM[%d] updated: Process %d, Page %d, Last Accessed: %d\n",
                           start_frame, start_frame + 1, RAM[start_frame]->process_id,
                           RAM[start_frame]->page_num, RAM[start_frame]->last_accessed);

                    counter_p0++; // Increment counter for process 0's page number
                }

                // Print RAM contents for debugging
                printf("RAM Contents after request from Process 0:\n");
                for (int k = 0; k < RAM_SIZE; k++) {
                    if (RAM[k] != NULL) {
                        printf("Frame %d: Process %d, Page %d, Last Accessed: %d\n",
                               k, RAM[k]->process_id, RAM[k]->page_num, RAM[k]->last_accessed);
                    } else {
                        printf("Frame %d: Empty\n", k);
                    }
                }
            }

            // Add similar logic for other processes here (process 1, 2, 3).
            else if (pid == 1) {
                if (RAM[start_frame] == NULL && RAM[start_frame + 1] == NULL) {
                    RAM[start_frame] = (struct memory*)malloc(sizeof(struct memory));
                    RAM[start_frame + 1] = (struct memory*)malloc(sizeof(struct memory));

                    RAM[start_frame]->process_id = pid;
                    RAM[start_frame]->page_num = counter_p1 % NUM_PAGES;
                    RAM[start_frame]->last_accessed = time;

                    RAM[start_frame + 1]->process_id = pid;  // Duplicate in the next frame
                    RAM[start_frame + 1]->page_num = counter_p1 % NUM_PAGES;
                    RAM[start_frame + 1]->last_accessed = time;

                    page_table[pid][counter_p1 % NUM_PAGES] = RAM[start_frame]->page_num;

                    printf("RAM[%d] and RAM[%d] updated: Process %d, Page %d, Last Accessed: %d\n",
                           start_frame, start_frame + 1, RAM[start_frame]->process_id,
                           RAM[start_frame]->page_num, RAM[start_frame]->last_accessed);

                    counter_p1++;
                }
            }
            else if (pid == 2) {
                if (RAM[start_frame] == NULL && RAM[start_frame + 1] == NULL) {
                    RAM[start_frame] = (struct memory*)malloc(sizeof(struct memory));
                    RAM[start_frame + 1] = (struct memory*)malloc(sizeof(struct memory));

                    RAM[start_frame]->process_id = pid;
                    RAM[start_frame]->page_num = counter_p2 % NUM_PAGES;
                    RAM[start_frame]->last_accessed = time;

                    RAM[start_frame + 1]->process_id = pid;  // Duplicate in the next frame
                    RAM[start_frame + 1]->page_num = counter_p2 % NUM_PAGES;
                    RAM[start_frame + 1]->last_accessed = time;

                    page_table[pid][counter_p2 % NUM_PAGES] = RAM[start_frame]->page_num;

                    printf("RAM[%d] and RAM[%d] updated: Process %d, Page %d, Last Accessed: %d\n",
                           start_frame, start_frame + 1, RAM[start_frame]->process_id,
                           RAM[start_frame]->page_num, RAM[start_frame]->last_accessed);

                    counter_p2++;
                }
            }
            else if (pid == 3) {
                if (RAM[start_frame] == NULL && RAM[start_frame + 1] == NULL) {
                    RAM[start_frame] = (struct memory*)malloc(sizeof(struct memory));
                    RAM[start_frame + 1] = (struct memory*)malloc(sizeof(struct memory));

                    RAM[start_frame]->process_id = pid;
                    RAM[start_frame]->page_num = counter_p3 % NUM_PAGES;
                    RAM[start_frame]->last_accessed = time;

                    RAM[start_frame + 1]->process_id = pid;  // Duplicate in the next frame
                    RAM[start_frame + 1]->page_num = counter_p3 % NUM_PAGES;
                    RAM[start_frame + 1]->last_accessed = time;

                    page_table[pid][counter_p3 % NUM_PAGES] = RAM[start_frame]->page_num;

                    printf("RAM[%d] and RAM[%d] updated: Process %d, Page %d, Last Accessed: %d\n",
                           start_frame, start_frame + 1, RAM[start_frame]->process_id,
                           RAM[start_frame]->page_num, RAM[start_frame]->last_accessed);

                    counter_p3++;
                }
            }

            // Print RAM contents after each access
            printf("RAM Contents after request from Process %d:\n", pid);
            for (int k = 0; k < RAM_SIZE; k++) {
                if (RAM[k] != NULL) {
                    printf("Frame %d: Process %d, Page %d, Last Accessed: %d\n",
                           k, RAM[k]->process_id, RAM[k]->page_num, RAM[k]->last_accessed);
                } else {
                    printf("Frame %d: Empty\n", k);
                }
            }
        } else {
            printf("Error: No two consecutive frames available for process %d\n", pid);
        }
        time++; // Increment the time step after each access
    }

    // Free allocated memory
    for (int i = 0; i < RAM_SIZE; i++) {
        if (RAM[i] != NULL) {
            free(RAM[i]);
        }
    }

    return 0;
}
