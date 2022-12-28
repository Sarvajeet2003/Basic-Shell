#include <stdlib.h>
#include <stdio.h>
#include "mySyscall.c"
int main()
{
  /* Call the print_process_info system call for the init process */
  syscall(__NR_print_process_info, 1);
  return 0;
}