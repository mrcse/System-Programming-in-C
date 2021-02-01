#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h> 

void showReturnStatus(pid_t childpid,int status) {
   
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
    int size=atoi(argv[1]);
    int i,x,status=0;
    pid_t pid;
    printf("\nParent PID[%d] PPID[%d]\n",getpid(),getppid());
    for( i=0;i<size;i++){
        
        x=fork();
        if(x>0)
            break;
    }
    // pid=wait(&status);  
    // showReturnStatus(pid,status);
    printf("\nValue of i : %d Proces ID : %d Parent Proces ID : %d Value of Fork  : %d\n",i,getpid(),getppid(),x);
    while(1);
    return 0;
}