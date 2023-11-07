# OS-Assignment-3
OS Assignment 3 by Tejas Jaiswal 2022538, Pranshu Goel 2022369

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MeMS (Memory Management System)

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


Overview

MeMS is a custom memory management system implemented in C that utilizes the mmap and munmap system calls for memory allocation and deallocation. It adheres to specific constraints and requirements, as outlined in the problem statement.


-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Assumptions

The code includes some assumptions, as not all details were clear in the provided documentation.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Functions :

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void mems_init()

This function initializes the MeMS (Memory Management System).
It sets up the initial state of the system, including the head of the free list and other global parameters.
The head of the free list is created using mmap, and it represents the main chain.
The function is typically called at the start of your program to prepare the MeMS system for memory management.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void mems_finish()

This function is responsible for cleaning up the MeMS system.
It iterates through the main chain and sub-chains, deallocating all the memory allocated by MeMS using munmap.
It should be called at the end of your program to release all the MeMS-allocated memory.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void* mems_malloc(size_t size)

mems_malloc is used for memory allocation.
It takes the size of memory requested by the user program as input and returns a MeMS virtual address.
The function first checks if there are any sufficiently large segments available in the free list to fulfill the request.
If not, it uses mmap to allocate more memory, creating a new main chain node and sub-chain nodes to represent the allocated memory.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void mems_free(void* ptr)
mems_free is used to free the memory pointed to by the MeMS virtual address ptr.
It marks the corresponding sub-chain node in the free list as HOLE, making that memory segment available for future allocations.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void mems_print_stats()

This function is for printing MeMS system statistics.
It provides information about how many pages are utilized, how much memory is unused, and details about each node in the main chain and each segment (PROCESS or HOLE) in the sub-chain.
It helps you monitor the memory usage and allocation patterns in the MeMS system.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void mems_get(void v_ptr)

mems_get returns the MeMS physical address mapped to the MeMS virtual address v_ptr.
This function is used to map a virtual address back to its physical location, which can be useful for debugging and other purposes.
These functions collectively provide memory management capabilities using MeMS. It's important to understand how they work and the underlying data structures they use for managing memory segments. Additionally, the code includes helper functions and data structures, such as the main chain and sub-chain, to manage memory allocation and deallocation.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Usage

This MeMS system is designed for a single process's memory management. You can call the provided functions for memory allocation and deallocation within your program.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Important Notes

The code uses a custom data structure for the free list, consisting of main chains and sub-chains to manage memory segments.

MeMS maintains the mapping from MeMS virtual addresses to MeMS physical addresses.

The code includes helper functions like HEXA_TO_DECIMAL for converting hexadecimal strings to decimal values.

The provided code demonstrates a basic implementation of MeMS with some assumptions, and further testing and refinements may be required.

Feel free to adapt the code and functions as needed for your specific use case and requirements.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


