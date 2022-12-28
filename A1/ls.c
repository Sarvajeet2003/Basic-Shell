#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

void lsCommand(const char *dir,int op_a,int op_l)
{
	struct dirent *d;
	DIR *B = opendir(dir);
	if (!B)
	{
		if (errno != ENOENT)
		{
			perror("Unable to read the directory");
		}
		else
		{
            perror("This Directory doesn't exist");
		}
		exit(EXIT_FAILURE);
	}

    d = readdir(B);

	while ((d=readdir(B)) != NULL)
	{
		if (!op_a && d->d_name[0] == '.'){
			continue;
        }

		printf("%s  ", d->d_name);

		if(op_l){
            printf("\n");
        }
	}
	if(!op_l){
	    printf("\n");
    }


}
int main(int A, const char *argv[])
{
	if (A == 2)
	{
        if (argv[1][0] == '-')
		{
			int op_a = 0;
            int op_l = 0;
			char *p = (char*)(argv[1] + 1);
			while(*p){
				if(*p == 'l'){
                    op_l = 1;
                }
				else if(*p == 'a'){
                    op_a = 1;
                }
				else{
					perror("Not Applicable");
					exit(EXIT_FAILURE);
				}
				p = p+1;
			}
			lsCommand(".",op_a,op_l);
		}
		
	}
	else if (A == 1)
	{
		lsCommand(".",0,0);
	}
	return 0;
}
