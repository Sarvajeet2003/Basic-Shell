#include<stdio.h>
#include<time.h>

int main()
{
    time_t CurrentTime = time(NULL);
    printf("Current date and time is : %s", ctime(&CurrentTime));
}