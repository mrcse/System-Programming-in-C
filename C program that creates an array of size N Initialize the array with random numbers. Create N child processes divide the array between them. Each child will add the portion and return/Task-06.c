#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

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
        printf("\n      Task-06.out required command-line arguments [ArraySize][No.Process]\n\n");
        return 0;
     }
    srand(time(0));                   
    int arraySize=atoi(argv[1]),noProcess=atoi(argv[2]),dataArray[arraySize],status=0;
    pid_t pid;
    int parentSum=0,parentArray[noProcess],fd[2];       //fd file descriptor

    if(pipe(fd)<0)      //check error in pipe system call
        return 0;

    for(int i=0 ;i<arraySize;i++)
        dataArray[i]=(rand()%100)+1;        // initialize array with random numbers
    
    for(int child=0 ; child < noProcess ; child++){
        int childProcess=fork();        //fork() system call to create process
        int childSum;
        if(childProcess==0){        //condition for child process to perform specific task
            close(fd[0]);       //close reading end of pipe
            childSum=0.0;       //initialize childSum to 0 in every child process

            for(int i=child*noProcess;i<(child+1)*noProcess;i++)        //divide dataArray by noProcess
                childSum+=dataArray[i];     //child calculate there sum 

            printf("\nChild Process No [%d] PID[%d] Parent PID[%d] Return Sum : %d \n",child,getpid(),getppid(),childSum);
            write(fd[1],&childSum,sizeof(childSum));    //writing data on pipe
            close(fd[1]);       //close writing end of pipe
            exit(0);        //exit child process after calculating sum with exit success
        }
        pid=wait(&status);      //wait() system call parent wait for child process
        showReturnStatus(pid,status);       //show wait status 
        read(fd[0],&parentArray[child],sizeof(parentArray));    //read data from child process
        parentSum+=parentArray[child];      //calculating parent sum or Final sum result

    }

    printf("\nParent Process PID [%d] Total Sum of Array :",getpid());
    for(int i=0;i<noProcess;i++){
        printf(" %d ",parentArray[i]);
        if(i==noProcess-1)
            printf("");
        else
            printf("+");
    }
    printf("= %d\n\n",parentSum);   
    return 0;
}
    