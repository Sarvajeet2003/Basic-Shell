#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

int main(int argc, char *argv[])
{
    mkfifo("myfifo", 0777);
    int fd = open("myfifo", O_RDONLY);
    if (fd < 0)
    {
        perror("ERROR, could not open File");
        return 1;
    }
    else
    {
        int count = 0;
        clock_t start_time = clock();
        while (count < 50)
        {
            int current_idx;
            read(fd, &current_idx, sizeof(int));
            for (int i = 0; i < 5; i++)
            {
                char string[5];
                read(fd, string, 5);
                printf("ID: %d, String: %s\n", current_idx + 1, string);
                // sleep(1);
                current_idx++;
                count++;
            }
            write(fd, &current_idx, sizeof(int));
        }
        clock_t end_time = clock();
        double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Elapsed time: %f seconds\n", elapsed_time);
        close(fd);
    }
    return 0;
}