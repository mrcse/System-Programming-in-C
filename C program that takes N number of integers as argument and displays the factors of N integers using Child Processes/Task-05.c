#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <unistd.h> 

void showFactor(int num){
    printf("\nFactors of %d are : \n ",num);
    for(int i=1; i<=num; i++)
    {
        if(num % i == 0)
            printf("%d, ",i);
    }
    printf("\n");
}

void showReturnStatus(pid_t childpid,int status){
    if (WIFEXITED(status) && !WEXITSTATUS(status))
        printf("Child %ld terminated normally\n", (long)childpid);
    else if (WIFEXITED(status))
        printf("Child %ld terminated with return status %d\n",(long)childpid, WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("Child %ld terminated due to uncaught signal %d\n",(long)childpid, WTERMSIG(status));
    else if (WIFSTOPPED(status))
        printf("Child %ld stopped due to signal %d\n",(long)childpid, WSTOPSIG(status));
}

int main(int argc, char *argv[]){

    if(argc==1){    //argv[0]==argc==0 which is file Name
        printf("Program Error:");
        printf("\n      Task-05.out required command-line argument [Numbers]\n\n");
        return 0;
     }
    int size=argc,userValues[size],x,status=0;
    pid_t pid;

    for(int i=1;i<size;i++){
        userValues[i]=atoi(argv[i]);
    }
    printf("\nParent ID : %d\n",getppid());
    for(int i=1;i<size;i++){
        x=fork();
        if(x==0){
            showFactor(userValues[i]);
            exit(0);
        }
        pid=wait(&status);
        showReturnStatus(pid,status);
    }
    return 0;
}