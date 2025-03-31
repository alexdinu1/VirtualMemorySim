# Virtual Memory Management Simulation
**By Alex Dinu and Alysha Prompruek (UWA)**

## Overview
This project is a simulation of a simple virtual memory management system using paging. It simulates a system with multiple processes that request pages, which are loaded into RAM when available.

## Features
- Simulates **4 processes**, each with **4 pages**.
- Uses a **16-slot RAM** divided into **8 frames**, where each page occupies **2 slots**.
- Implements a simple **page allocation** strategy, searching for **two consecutive free frames** to allocate a new page.
- Maintains a **page table** for each process, marking pages as **in virtual memory (99)** or **loaded into RAM**.
- Reads a sequence of process IDs from an **input file (`in.txt`)**, determining the page requests dynamically.
- Prints the **RAM state** and **page tables** after each allocation.
- Handles **memory deallocation** at the end of the program.

## File Structure
- `main.c` - The source code implementing the virtual memory simulation.
- `in.txt` - Input file containing a sequence of process IDs (each representing a page request).
- `README.md` - This documentation.

## Compilation & Execution
To compile the program, use `gcc`:
```sh
gcc -o vm_simulator main.c
```
To run the program:
```sh
./vm_simulator
```
Ensure `in.txt` exists in the same directory and contains space-separated or newline-separated integers representing process IDs.

## Example Input (`in.txt`)
```
0 1 2 3 0 1 2 3 0 1 2 3
```

## Example Output
```
Process IDs read from file:
0 1 2 3 0 1 2 3 0 1 2 3

Page tables initialized to virtual memory:
Process 0: 99 99 99 99
Process 1: 99 99 99 99
Process 2: 99 99 99 99
Process 3: 99 99 99 99

RAM[0] and RAM[1] updated: Process 0, Page 0, Last Accessed: 0
...
Frame 0: Process 0, Page 0, Last Accessed: 0
Frame 1: Process 0, Page 0, Last Accessed: 0
Frame 2: Empty
...
```

## Future Enhancements
- Implement **page replacement algorithms** (FIFO, LRU, etc.).
- Improve RAM utilization and optimize memory management.
- Support for dynamic process creation and termination.


