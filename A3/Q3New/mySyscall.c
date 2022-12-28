#include <stdio.h>
#include <stdlib.h>
#include <linux/sched.h>

// HERE SET THE NUMBER ACCORDING TO THE KERNEL
#define __NR_print_process_info 287

SYSCALL_DEFINE1(process, pid_t, pid)
{
  struct task_struct task;
  task = pid_task(find_vpid(pid), pid_t);
  printk("The Process ID is: %d\n", task.pid);
  printk("The User ID is: %d\n", task.cred.uid.val);
  printk("The Process Group ID is: %d\n", task.group_leader.pid);
  printk("The Command Path is: %s\n", task.comm);

  return 0;
}
