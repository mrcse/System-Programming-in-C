#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int x;
    for(int i=1;i<=2;i++){
        x=fork();
        
        switch (i)
        {
        case 1:
        if(x==-1)
            perror("\nFailed to create Child Process\n");
        else if (x==0){
            execvp("./addArray",argv);
            perror("\nexeclp() System call Error\n");
            exit(0);
        }
            break;
        
        case 2:
            if(x==-1)
            perror("\nFailed to create Child Process\n");
            else if (x==0){
            execvp("./multArray",argv);
            perror("\nexeclp() System call Error\n");
            exit(0);
            }
            break;
        }
    }
    for(int i=0;i<2;i++)
        wait(NULL);
    printf("\n\n\t\tMain Program End\n\n");
    return 0;
}