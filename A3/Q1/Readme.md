# Sarvajeeth U K
# 2021417 CSSS

1. A_Semaphore:

The program defines an array of semaphores forks to represent the forks that the philosophers need to eat. The philosophers are represented by threads that are created and managed using the pthread library.

Each philosopher thread repeatedly performs the following steps:

    1. Prints a message indicating that it is thinking.
    2. Sleeps for 2 seconds.
    3. Prints a message indicating that it is hungry.
    4. Acquires the semaphores for the left and right forks, using the sem_wait function.
    5. Prints a message indicating that it is eating.
    6. Sleeps for 2 seconds.
    7. Releases the semaphores for the left and right forks, using the sem_post function.
    8. Prints a message indicating that it has finished eating.


2. A_StrictOrdering:

The program defines an array of integers forks to represent the forks that the philosophers need to eat. The philosophers are represented by threads that are created and managed using the pthread library.

Each philosopher thread repeatedly performs the following steps:

    1. Prints a message indicating that it is thinking.
    2. Sets the value of the left fork to 1, indicating that it has been picked up.
    3. Sleeps for 1 second.
    4. Prints a message indicating that it has picked up the left fork.
    5. Sets the value of the right fork to 1, indicating that it has been picked up.
    6. Prints a message indicating that it has picked up the right fork.
    7. Prints a message indicating that it is eating.
    8. Sets the value of the left and right forks back to 0, indicating that they have been released.
    9. Sleeps for 1 second.




3. B1:

The program defines an array of semaphores bowls to represent the bowls of rice that the philosophers need to eat. The philosophers are represented by threads that are created and managed using the pthread library.

Each philosopher thread repeatedly performs the following steps:

    1. Prints a message indicating that it is thinking.
    2. Waits on the semaphore for the left bowl.
    3. Sleeps for 1 second.
    4. Prints a message indicating that it has picked up the left bowl.
    5. Waits on the semaphore for the right bowl.
    6. Prints a message indicating that it has picked up the right bowl.
    7. Prints a message indicating that it is eating.
    8. Releases the semaphores for the left and right bowls.
    9. Sleeps for 1 second.
    10. The main function initializes the semaphores for the bowls and creates and joins the philosopher threads. It is set to run the simulation indefinitely in a loop.

This program can potentially run into a deadlock if all of the philosophers try to pick up their left bowls at the same time, as they will all be waiting on the semaphores and will not be able to proceed. This illustrates the need for resource allocation and synchronization strategies to avoid such problems.



4. B2:

This implementation is similar to the previous one, except that we use an array of semaphores bowls to represent the bowls of rice that the philosophers have. Each philosopher has two bowls, and they acquire the mutex before attempting to pick up either of them. After they have both bowls, they release the mutex and proceed to eat. When they are finished eating, they release the bowls and repeat the process.

The system call uses the pid_task function to retrieve the task_struct for the process with the given PID. The task_struct is a data structure that contains information about a process, such as its PID, user ID, process group ID, and command path.

The system call then prints this information using the printk function, which is used to print kernel messages.

Like the previous implementation, this version uses an infinite loop to allow the philosophers to continue eating and thinking indefinitely