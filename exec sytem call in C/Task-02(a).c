#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int x;
    x=fork();
    if(x==-1)
        printf("\nFailed to create Child Process\n");
    else if (x==0){
        execvp("./addArray",argv);
        perror("\nexeclp() System call Error\n");
        exit(0);
    }
    else
        wait(NULL);
    printf("\n\n\t\tMain Program End\n\n");
    return 0;
}