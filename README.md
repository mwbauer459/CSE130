# CSE130

Collection of assignments from CSE130. This class focused on Operating Systems and the implementation of various algorithms and semaphores to optimize system performance. There was a heavy focus on multithreading and learning to handle data cocurrently is separate threads and processes.

Assignment 1 - Sort given array within the alloted time period. In order to pass the test the array had to be divided recursively, with each division being handled by a new process, therefore completing multiple tasks concurrently and sorting the array in the alloted time. Implementation in sort.c. 

Assignment 2 - Same concept as assignment 1 except this time using threads. The challenge here was figuring out how to communicate between threads to ensure that data was sorted in the desired order and that the algorithm would finish only when all threads had completed their task. Implementation in sort.c.

Assignment 3 - Online test that hasn't been included in this repo

Assignment 4 - Two part assignment. Part one involved the use of threads and locks to correctly display a paragraph that was provided to us in the incorrect order. In order to properly display the paragraph, no thread could complete before all threads had completed their task. Locks were use to achieve this. Implementation in manpage.c. Part two involved the proper scheduling of a simulated cart and track system. We were given a variety of stipulations (such as cart 1 can only travel on the blue line going from point A to B,  cart 2 travels on the red line from C to B, etc.). Our job was to properly schedule these carts through the use threads, while ensuring no collisions and that all carts would complete their course within a given time frame.  To do this, we had to implement a system of locks that would prevent carts trying to travel on the same track from going at the same, while allowing multiple carts to travel on seperate tracks concurrently. Implementation in cartman.c. 


