#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int min;
    int max;
    int x;
    for(int i=1;i<=2;i++){
        x=fork();
        
        switch (i)
        {
        case 1:
        if(x==-1)
            perror("\nFailed to create Child Process\n");
        else if (x==0){
            execvp("./minArray",argv);
            perror("\nexeclp() System call Error\n");
            exit(0);
        }
            break;
        
        case 2:
            if(x==-1)
            perror("\nFailed to create Child Process\n");
            else if (x==0){
            execvp("./maxArray",argv);
            perror("\nexeclp() System call Error\n");
            exit(0);
            }
            break;
        }
    }
    wait(&min);
    wait(&max);
    printf("\nMin Value among the Array is : %d\n",WEXITSTATUS(min));
    printf("\nMax Value among the Array is : %d\n",WEXITSTATUS(max));
    printf("\n\n\t\tMain Program End\n\n");
    return 0;
}