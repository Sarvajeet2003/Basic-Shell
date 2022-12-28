#include<stdio.h>
int main() {

    char A[20];
    printf("Enter the FileName you wish to Deleted: ");
    scanf("%s",A);
    int del = remove(A);
    if (!del)
        printf("The file is Deleted successfully");
    else
        printf("the file is not Deleted");
    return 0;
}