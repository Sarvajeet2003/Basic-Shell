#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int forks[5];

void *philosopher(void *arg)
{
    int id = *((int *)arg)+1;
    int left = id;
    int right = (id + 1) % 5;
    printf("Philosopher %d is thinking\n", id);
    forks[left] = 1;
    sleep(1);
    printf("Philosopher %d picked up left fork\n", id);
    forks[right] = 1;
    printf("Philosopher %d picked up right fork\n", id);
    printf("Philosopher %d is eating in his Bowl\n", id);
    forks[left] = 0;
    forks[right] = 0;
    sleep(1);
    return NULL;
}

int main()
{

    while(1){
    for (int i = 0; i < 5; i++)
    {
        forks[i] = 0;
    }
    
    pthread_t philosophers[5];
    int ids[5];

    for (int i = 0; i < 5; i++)
        {
            ids[i] = i;
            pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
        }

    for (int i = 0; i < 5; i++)
        {
            pthread_join(philosophers[i], NULL);
        }
    }
    return 0;
}
