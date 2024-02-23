# Operating Systems Concepts' Projects
Operating Systems Projects for my Bachelor course, based on projects from the "Operating Systems Concepts" 9th edition book. Language used: Albanian. Finished and handed in 2022.

### Description of each Problem:
In the folder `linked-lists` is the project of Chapter 2 that reads as follows:
* In the module entry point, create a linked list containing five struct birthday elements. Traverse the linked list   and output its contents to the kernel log buffer. Invoke the dmesg command to ensure the list is properly constructed once the kernel module has been loaded.
* In the module exit point, delete the elements from the linked   list and return the free memory back to the kernel. Again, invoke the dmesg command to check that the list has been removed once the kernel module has been unloaded.

In the folder `producer-consumer` is the project of Chapter 5 that reads as follows:
* You will design a programming solution to the bounded-buffer problem using the producer and consumer processes.
* The solution presented uses 3 semaphores: empty and full, which count the number of empty and full slots in the buffer, and mutex, which is a binary (or mutualexclusion) semaphore that protects the actual insertion or removal of items in the buffer.
* For this project, you will use standard counting semaphores for empty and full and a mutex lock, rather than a binary semaphore, to represent mutex.
* The producer and consumer — running as separate threads — will move items to and from a buffer that is synchronized with the empty, full, and mutex structures.
