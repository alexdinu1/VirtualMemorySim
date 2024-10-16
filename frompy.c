#include <stdio.h>
#include <stdlib.h>

#define NUM_PROCESSES 4    // Number of processes
#define NUM_PAGES NUM_PROCESSES        // Number of pages per process
#define RAM_SIZE 16        // Size of RAM (16 slots, 8 frames)
#define PAGE_SIZE 2        // Number of slots per page (2 slots)
#define MAX_LINE_LENGTH 100 // Maximum length for a line in the input file
#define IN_VIRTUAL_MEMORY 99 // Indicator that a page is in virtual memory

typedef struct {
    int process_id;
    int page_number;
    int time;
} RAM_entry;

RAM_entry RAM[RAM_SIZE];  // Array to hold RAM entries
int ram_count = 0;        // Counter for current number of entries in RAM

void add_to_RAM(int process_id, int page_number, int time) {
    if (ram_count < RAM_SIZE) {
        // Add the new entry if RAM is not full
        RAM[ram_count].process_id = process_id;
        RAM[ram_count].page_number = page_number;
        RAM[ram_count].time = time;
        ram_count++;
    } else {
        // RAM is full, need to remove the oldest entry for the same process
        int min_time = time;
        int min_index = -1;

        // Find the entry with the minimum time for the same process_id
        for (int i = 0; i < RAM_SIZE; i++) {
            if (RAM[i].process_id == process_id && RAM[i].time < min_time) {
                min_time = RAM[i].time;
                min_index = i;
            }
        }

        // Replace the oldest entry if we found an old entry with the same process_id
        if (min_index != -1) {
            RAM[min_index].process_id = process_id;
            RAM[min_index].page_number = page_number;
            RAM[min_index].time = time;
        }
    }
}

// Comparator function to sort RAM by the 'time' field (element 2 of the tuple)
int compare_by_time(const void *a, const void *b) {
    RAM_entry *entryA = (RAM_entry *)a;
    RAM_entry *entryB = (RAM_entry *)b;
    
    return entryA->time - entryB->time;
}

void sort_RAM_by_time() {
    qsort(RAM, ram_count, sizeof(RAM_entry), compare_by_time);
}

int find_in_RAM(int process_id, int page_number) {
    // Check if the (process_id, page_number) exists in the RAM
    for (int i = 0; i < ram_count; i++) {
        if (RAM[i].process_id == process_id && RAM[i].page_number == page_number) {
            return i; // Return the index of the RAM entry
        }
    }
    return -1; // Return -1 if not found
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("Error: Could not open input file\n");
        return 1;
    }

    // Open the output file
    FILE *output_file = fopen(argv[2], "w");
    if (!output_file) {
        printf("Error: Could not open output file\n");
        fclose(input_file);
        return 1;
    }

    // Read integers from the input file
    int process_ids[100];  // Adjust size based on input file's expected size
    int index = 0;

    while (fscanf(input_file, "%d", &process_ids[index]) == 1) {
        index++;
    }

    fclose(input_file);

    int time = 0;
    int p0 = 0, p1 = 0, p2 = 0, p3 = 0;

    // Processing each process ID
    for (int i = 0; i < index; i++) {
        switch (process_ids[i]) {
            case 0:
                add_to_RAM(0, p0 % NUM_PROCESSES, time);
                add_to_RAM(0, p0 % NUM_PROCESSES, time);
                p0++;
                time++;
                break;
            case 1:
                add_to_RAM(1, p1 % NUM_PROCESSES, time);
                add_to_RAM(1, p1 % NUM_PROCESSES, time);
                p1++;
                time++;
                break;
            case 2:
                add_to_RAM(2, p2 % NUM_PROCESSES, time);
                add_to_RAM(2, p2 % NUM_PROCESSES, time);
                p2++;
                time++;
                break;
            case 3:
                add_to_RAM(3, p3 % NUM_PROCESSES, time);
                add_to_RAM(3, p3 % NUM_PROCESSES, time);
                p3++;
                time++;
                break;
            default:
                fprintf(output_file, "Error: Invalid process ID\n");
                break;
        }
    }

    // Sort RAM by time before output
    sort_RAM_by_time();

    fprintf(output_file, "Processes: \n");

    for (int process_id = 0; process_id < NUM_PROCESSES; process_id++) {
        fprintf(output_file, "Process %d: ", process_id);
        for (int page_number = 0; page_number < NUM_PAGES; page_number++) {
            int ram_index = find_in_RAM(process_id, page_number);
            if (ram_index != -1) {
                // If the tuple is in RAM, print the actual values
                fprintf(output_file, "%d", ram_index/2);
            } else {
                // If the tuple is not in RAM, print (process_id, page_number, 99)
                fprintf(output_file, "99");
            }
            if (page_number < NUM_PAGES - 1) {
                fprintf(output_file, ", "); // Add ', ' between tuples
            }
        }
        fprintf(output_file, "\n"); // Newline after each process's output
    }

    fprintf(output_file, "\n");  // Newline after output


    // Output the RAM content in the format: process_id,page_number,time;
    fprintf(output_file, "RAM content:\n");
    for (int i = 0; i < ram_count; i++) {
        fprintf(output_file, "%d,%d,%d", RAM[i].process_id, RAM[i].page_number, RAM[i].time);
        if (i < ram_count - 1) {
            fprintf(output_file, "; ");  // Add '; ' between entries, no semicolon after the last one
        }
    }
    
    

    fclose(output_file);

    return 0;
}
