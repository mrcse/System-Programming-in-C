#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>

int main(int argc, char *argv[]){
    int numProcess=argc;

    for(int i=0;i<numProcess;i++){
        int x=fork();
        if(x==0){
            execlp(argv[i+1],argv[i+1],NULL);
            printf("\nexeclp() System call Error for \"%s\" : %s\n",argv[i+1],strerror(errno));
            exit(0);
        }
    }
    for (int i=0;i<numProcess;i++)
        wait(NULL);
    printf("\n Main Program End\n");
    return 0;
}