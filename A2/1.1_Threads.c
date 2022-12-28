#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>


void *thread_functionA(void *arg);
void *thread_functionB(void *arg);
void *thread_functionC(void *arg);
clock_t beginA;
clock_t beginB;
clock_t beginC;
double time_spentA;
double time_spentB;
double time_spentC;


void *thread_functionA (void *arg){
    printf ("Inside Function A\n");
        for(long long i=1;i<=pow(2,32);i++){

        }
    clock_t endA = clock();
    time_spentA = (double)(endA - beginA) / CLOCKS_PER_SEC;
    printf("%lf\n",time_spentA);
    return 0;
}

void *thread_functionB (void *arg){
    printf ("Inside Function B\n");
        for(long long i=1;i<=pow(2,32);i++){

        }
    clock_t endB = clock();
    time_spentB = (double)(endB - beginB) / CLOCKS_PER_SEC;
    printf("%lf\n",time_spentB);
    return 0;
}

void *thread_functionC (void *arg){
    printf ("Inside Function C\n");
        for(long long  i=1;i<=pow(2,32);i++){

        }
    clock_t endC = clock();
    time_spentC = (double)(endC - beginC) / CLOCKS_PER_SEC;
    printf("%lf\n",time_spentC);
    return 0;
}



int main() {

pthread_attr_t a;
pthread_attr_t b;
pthread_attr_t c;

pthread_t a_thread;
pthread_t b_thread;
pthread_t c_thread;

int	 pthread_setschedparam(pthread_t tid, int policy,const struct sched_param *param);
struct sched_param param;

pthread_attr_setschedpolicy(&a, SCHED_OTHER);
pthread_attr_setschedpolicy(&b, SCHED_RR);
pthread_attr_setschedpolicy(&c, SCHED_FIFO);

pthread_setschedparam(a_thread, 0, &param);
pthread_setschedparam(b_thread, 50, &param);
pthread_setschedparam(c_thread, 50, &param);

pthread_create(&a_thread, NULL, thread_functionA, NULL);
beginA = clock();
pthread_create(&b_thread, NULL, thread_functionB, NULL); 
beginB = clock();
pthread_create(&c_thread, NULL, thread_functionC, NULL);
beginC = clock();

pthread_join(a_thread, NULL);
pthread_join(b_thread, NULL);
pthread_join(c_thread, NULL);

}    



