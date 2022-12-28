#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void where(void)
{
    char buffer[1024];

    if (getcwd(buffer, sizeof(buffer)) == NULL)
    {
        abort();
    }

    printf("current directory is %s\n",buffer);

    printf("environment variable says %s\n",getenv("PWD"));

}

int main(void)
{
    system("rm -rf subdirectory");

    if (mkdir("subdirectory", 0700)){
        abort();
    }

    printf("before changing directory:\n");

    where();

    if (chdir("subdirectory")){
        abort();
    }

    printf("after  changing directory:\n");

    where();

    return 0;

} /* main() */