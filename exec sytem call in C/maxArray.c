#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    int size=argc;
    int max=atoi(argv[1]);
    for(int i=1;i<size;i++)
        if(max<atoi(argv[i]))
            max=atoi(argv[i]);
    return max;
}