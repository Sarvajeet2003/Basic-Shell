#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char strings[50][5];
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            strings[i][j] = 'a' + rand() % 26;
        }
    }
    int fd = open("myfifo", O_WRONLY);
        int current_idx = 0;
        while (current_idx < 50)
        {
            write(fd, &current_idx, sizeof(int));
            for (int i = 0; i < 5; i++)
            {
                if (current_idx >= 50)
                {
                    break;
                }
                write(fd, strings[current_idx], 5);
                current_idx++;
            }
            int acknowledged_idx;
            read(fd, &acknowledged_idx, sizeof(int));
        }

        close(fd);
    return 0;
}