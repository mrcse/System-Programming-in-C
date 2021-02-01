#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
 
#define BUFF_SIZE 1024
 
int main(int argc, char* argv[]){

    if(argc < 3){
		printf("\nError: %s required arguments [source_file] [destination_file]...and so on\n\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	int srcFD[argc],destFD[argc],numBytesRead,nbwrite;
	char *buff[BUFF_SIZE];
    mode_t fdmode = (S_IRWXU | S_IRGRP | S_IROTH);
 
    for(int i=1 ;i <argc ;i+=2){
        //Open source file READ_ONLY
        srcFD[i] = open(argv[i],O_RDONLY);
    
        if(srcFD[i] == -1){
            printf("\nError: cannot open '%s' : %s\n",argv[i],strerror(errno));
            exit(EXIT_FAILURE);	
        }
        
        
        destFD[i] = open(argv[i+1],O_WRONLY | O_CREAT | O_EXCL, fdmode);
    
        if(destFD[i] == -1){
            printf("\nError: cannot open '%s' : %s\n",argv[i+1],strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    for(int i=1 ;i <argc ;i+=2){
        while((numBytesRead=read(srcFD[i],buff,BUFF_SIZE))>0)
        if(write(destFD[i],buff,numBytesRead) != numBytesRead)
			printf("\nError: writing data to %s\n",argv[i+1]);
        
        if(numBytesRead == -1)
		printf("\nError: reading data from %s\n",argv[i]);
	
        if(close(srcFD[i]) == -1)
            printf("\nError: closing file %s\n",argv[i]);
    
        if(close(destFD[i]) == -1)
            printf("\nError: closing file %s\n",argv[i+1]);
    }
    return 0;
}