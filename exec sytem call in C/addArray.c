#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    int size=argc;
    int sum=0;
    for(int i=1;i<size;i++)
        sum+=atoi(argv[i]);
    printf("\nSum of the Array is : %d\n\n",sum);
    return 0;
}