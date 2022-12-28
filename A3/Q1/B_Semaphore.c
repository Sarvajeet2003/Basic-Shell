#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int bowls[2];

void *philosopher(void *arg){

  int id = *((int *)arg)+1;
  int left = id % 2;
  int right = (id + 1) % 2;

    printf("Philosopher %d is thinking\n", id);
    sem_wait(&bowls[left]);
    sleep(1);
    printf("Philosopher %d picked up left bowl\n", id);
    sem_wait(&bowls[right]);
    printf("Philosopher %d picked up right bowl\n", id);
    printf("Philosopher %d is eating\n", id);
    sem_post(&bowls[left]);
    sem_post(&bowls[right]);
    sleep(1);

  return 0;
}

int main(){

while(1){
  for (int i = 0; i < 2; i++) 
  {
    sem_init(&bowls[i], 0, 1);
  }

  pthread_t philosophers[5];
  int ids[5];

  for (int i = 0; i < 5; i++) 
  {
    ids[i] = i;
    pthread_create(&philosophers[i], 0, philosopher, &ids[i]);
  }

  for (int i = 0; i < 5; i++) 
  {
    pthread_join(philosophers[i], 0);
  }
}
  return 0;
}
