#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include<time.h>

int main() {
  key_t key = ftok("SHARED_MEM", 65);
  int shmid = shmget(key, 1024, 0666|IPC_CREAT);
  char* shared_memory = shmat(shmid, (void*)0, 0);
  char string_array[50][5];  
  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 5; j++) {
      string_array[i][j] = 'a' + rand() % 26;
    }
  }

  
  int current_index = 0; 
  while (current_index < 50) {
    for (int i = 0; i < 5; i++) {
      int index = current_index + i;
      if (index >= 50) break; 
      shared_memory += 10;
    }
    int acknowledged_id = -1;
    while (acknowledged_id < 0) {
      sscanf(shared_memory, "%d", &acknowledged_id);
    }
    current_index += 5;
  }
    

  shmdt(shared_memory);
  shmctl(shmid, IPC_RMID, NULL);

  return 0;
}
