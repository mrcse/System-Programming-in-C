#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
 
#define BUFF_SIZE 1024
 
int main(int argc, char* argv[])
{
	int srcFD,destFD,numBytesRead,nbwrite;
	char *buff[BUFF_SIZE];
    mode_t fdmode = (S_IRWXU | S_IRGRP | S_IROTH);
	if(argc%2!=1)
	{
		printf("\nError: %s required arguments [source_file] [destination_file]\n\n",argv[0]);
		exit(EXIT_FAILURE);
	}
    for(int i=1;i<argc;i+=2){
        int x=fork();
        if(x==0){
            //Open source file READ_ONLY
            srcFD = open(argv[i],O_RDONLY);
        
            if(srcFD == -1)
            {
                printf("\nError: cannot open '%s' : %s\n",argv[i],strerror(errno));
                exit(EXIT_FAILURE);	
            }
            
            
            destFD = open(argv[i+1],O_WRONLY | O_CREAT | O_EXCL, fdmode);
        
            if(destFD == -1)
            {
                printf("\nError: cannot open '%s' : %s\n",argv[i+1],strerror(errno));
                exit(EXIT_FAILURE);
            }
        
            //Start data transfer from src file to dest file till EOF
            while((numBytesRead = read(srcFD,buff,BUFF_SIZE)) > 0)
                if(write(destFD,buff,numBytesRead) != numBytesRead)
                    printf("\nError: writing data to %s\n",argv[i+1]);

            if(numBytesRead == -1)
                printf("\nError: reading data from %s\n",argv[i]);
            
            if(close(srcFD) == -1)
                printf("\nError: closing file %s\n",argv[i]);
        
            if(close(destFD) == -1)
                printf("\nError: closing file %s\n",argv[i+1]);
            return 0;
            }
    }
    for(int i=1;i<argc/2;i++)
        wait(NULL);
	
 
	return 0;
}