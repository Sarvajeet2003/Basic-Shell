#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* ptr;
	char ch;
    char s[100];
    printf("Enter the Name of the File: ");
    scanf("%s",s);
    printf("\n");
	ptr = fopen(s, "r");

    if(NULL !=ptr){
	    printf("Contents of this file are:  \n");
        printf("\n");
    }
	else {
		printf("file can't be opened \n");
	}
    while (ch != EOF){
        ch = fgetc(ptr);
		printf("%c", ch);
    }
    printf("\n");
	fclose(ptr);
	return 0;
}



