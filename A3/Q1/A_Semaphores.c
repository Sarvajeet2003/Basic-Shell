#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <dispatch/dispatch.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


sem_t forks[5];

void *philosopher_actions(void *philosopher_id)
{
  int id = *((int *)philosopher_id)+1;
  printf("Thinking: %d\n", id);
  sleep(2);
  printf("Hungry: %d\n", id);
  int fork1 = id;
  int fork2 = (id + 1);
  if (fork1 < fork2)
  {
    int temp = fork2;
    fork2 = fork1;
    fork1 = temp;
  }
  sem_wait(&forks[fork2]);
  sem_wait(&forks[fork1]);
  printf("Eating: %d\n", id);
  sleep(2);
  sem_post(&forks[fork2]);
  sem_post(&forks[fork1]);
  printf("Finished %d\n", id);

  return NULL;
}

int main(void)
{
  while (true)
  {
    for (int i = 0; i < 5; i++)
    {
      sem_init(&forks[i], 1, 0);
    }
    pthread_t philosophers[5];
    for (int i = 0; i < 5; i++)
    {
      int *id = malloc(sizeof(int));
      *id = i;
      pthread_create(&philosophers[i], NULL, philosopher_actions, id);
    
    }
    for (int i = 0; i < 5; i++)
    {
      pthread_join(philosophers[i], NULL);  
    }
  }
  return 0;
}
