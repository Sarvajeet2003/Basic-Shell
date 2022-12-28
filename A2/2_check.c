#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

#define __NR_kernel_2d_memcpy 448
int main()
{
    int n= 4, m = 8;
    int temp;
    float** source= (float**)malloc(n * sizeof(float*));

    for (int i= 0;i<n;i++){
        source[i] = (float*)malloc(m*sizeof(float));
    }

    for (int i= 0; i< n;i++){
        for (int j= 0;j < m;j++){
            source[i][j]=i+j+10.505;
        }
    }
    printf("First memory after calling syscall: \n");
    for (int i= 0;i<n;i++){
        int j=0;
        while(j<m){
            printf("%lf ",source[i][j]);
            j++;
        }
        printf("\n");
    }
    float** destination= (float**)malloc(n* sizeof(float*));
    for (int i = 0; i < n; i++){
        destination[i] = (float*)malloc(m * sizeof(float));
    }

    temp = syscall(__NR_kernel_2d_memcpy,source,destination,n,m);

    printf("Second memory after calling syscall : \n");
    for (int i= 0;i<n;i++){
        int j=0;
        while(j<m){
            printf("%lf ",destination[i][j]);
            j++;
        }
        printf("\n");
    }
    return 0;
}