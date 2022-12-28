#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    printf("Enter directory name You want to create: ");

    int ret = 0;

    char FolderName[16];
    scanf("%s", FolderName);

    ret = mkdir(FolderName, 0755);

    if(ret!=0){
        printf("Unable to create directory %s\n", FolderName);
    }

    if(ret==0){
        printf("Directory created successfully\n");
    }

    return 0;
}
