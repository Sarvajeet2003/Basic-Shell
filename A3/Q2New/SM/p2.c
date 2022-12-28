#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <time.h>


int main() {
  key_t key = ftok("SHARED_MEM", 65);
  int shmid = shmget(key, 1024, 0666|IPC_CREAT);
  char* shared_memory = shmat(shmid, (void*)0, 0);

  int acknowledged_id = 0;
  clock_t start_time = clock();
  while (acknowledged_id < 50) {
    for (int i = 0; i < 5; i++) {
      int id;
      char str[5];
      sscanf(shared_memory, "%d:%s", &id, str);
      printf("Received string with ID %d: %s\n", id, str);
      shared_memory += 5 + 3; 
    }
    sprintf(shared_memory, "%d", acknowledged_id + 5);
    acknowledged_id += 5;
  }
  clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);
  shmdt(shared_memory);

  return 0;
}

