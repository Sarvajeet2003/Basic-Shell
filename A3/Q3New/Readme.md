# Sarvajeeth U K
# 2021417 CSSS

In this Question, we are supposed to define a system call which Prints:
#   1. Process ID
#   2. User ID
#   3. Process Group ID
#   4. Command Path
A.

1. For this we define a Syscall which takes parameters as Process number, Process Type and Process ID

2. Next we create a task of type task_struct and pass the pid and pid_type to it.

3. Later we write the print statements which prints the values of Tasks which is required.

B.

1. Now we crete a C file to call the system call which we defined by passing the Process Nmuber and its ID as a parameter.

Now, We have successfully defined the system call in our kernel and called it using the Call.c program