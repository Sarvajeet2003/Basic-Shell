#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int bowls[2];
void* philosopher(void* arg)
{
    int id = *(int*)arg;
        printf("Philosopher %d is thinking.\n", id);
        sleep(1); 
        int bowl = id % 2;
        while (bowls[bowl] == 0) {
            bowl = (bowl + 1) % 2;
        }
        bowls[bowl] = 0;
        printf("Philosopher %d is eating.\n", id);
        sleep(1); 
        bowls[bowl] = 1;

    return 0;
}

int main()
{
    for (int i = 0; i < 2; i++) {
        bowls[i] = 1;
    }
    pthread_t philosophers[5];
    int philosopher_ids[5];
while(1){
    for (int i = 0; i < 5; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], 0, philosopher, &philosopher_ids[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(philosophers[i], 0);
    }
    }
    return 0;
}
