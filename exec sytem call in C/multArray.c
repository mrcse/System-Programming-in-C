#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    int size=argc;
    int product=1;
    for(int i=1;i<size;i++)
        product*=atoi(argv[i]);
    printf("\nProduct of the Array is : %d\n\n",product);
    return 0;
}