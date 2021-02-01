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
    int catOptions=argc;
	int srcFD,destFD,numBytesRead,nbwrite;
	char *buff[BUFF_SIZE];
    mode_t fdmode = (S_IRWXU | S_IRGRP | S_IROTH);
    
    switch(catOptions){
        case 1:
            while((numBytesRead=read(STDIN_FILENO,buff,1)>0)) //displaying the content
                if(write(STDOUT_FILENO,buff,1)==-1)
                    perror("\nFailed to write");
            break;
        
        case 2:
            srcFD=open(argv[1], O_RDONLY);
            if(srcFD==-1){
                printf("\nError: cannot open '%s' : %s\n",argv[1],strerror(errno));
                exit(EXIT_FAILURE);	
            }
            while((numBytesRead=read(srcFD,buff,BUFF_SIZE))>0) //displaying the content
                printf("%s",buff);
            printf ("\n");
            break;
        
        case 3:
            if(argv[2]!=">>"){
            printf("\nError: %s required arguments [source_file] [>'Truncat', >>'Append'] [destination_file]\n\n",argv[0]);
            exit(EXIT_FAILURE);
            }

            //Open source file READ_ONLY
            srcFD = open(argv[1],O_RDONLY);
        
            if(srcFD == -1){
                printf("\nError: cannot open '%s' : %s\n",argv[1],strerror(errno));
                exit(EXIT_FAILURE);	
            }
            
            destFD = open(argv[3],O_WRONLY | O_CREAT | O_APPEND, fdmode);
        
            if(destFD == -1){
                printf("\nError: cannot open '%s' : %s\n",argv[3],strerror(errno));
                exit(EXIT_FAILURE);
            }
        
            //Start data transfer from src file to dest file till EOF
            while((numBytesRead = read(srcFD,buff,BUFF_SIZE)) > 0)
                if(write(destFD,buff,numBytesRead) != numBytesRead)
                    printf("\nError: writing data to %s\n",argv[3]);

            if(numBytesRead == -1)
                printf("\nError: reading data from %s\n",argv[1]);
            
            if(close(srcFD) == -1)
                printf("\nError: closing file %s\n",argv[1]);
        
            if(close(destFD) == -1)
                printf("\nError: closing file %s\n",argv[3]);
            break;

        case 4:
            if(argv[2]!=">"){
            printf("\nError: %s required arguments [source_file] [>'Truncat', >>'Append'] [destination_file]\n",argv[0]);
            exit(EXIT_FAILURE);
            }

            //Open source file READ_ONLY
            srcFD = open(argv[1],O_RDONLY);
        
            if(srcFD == -1){
                printf("\nError: cannot open '%s' : %s\n",argv[1],strerror(errno));
                exit(EXIT_FAILURE);	
            }
            
            destFD = open(argv[3],O_WRONLY | O_CREAT | O_TRUNC, fdmode);
        
            if(destFD == -1){
                printf("\nError: cannot open '%s' : %s\n",argv[3],strerror(errno));
                exit(EXIT_FAILURE);
            }
        
            //Start data transfer from src file to dest file till EOF
            while((numBytesRead = read(srcFD,buff,BUFF_SIZE)) > 0)
                if(write(destFD,buff,numBytesRead) != numBytesRead)
                    printf("\nError: writing data to %s\n",argv[3]);

            if(numBytesRead == -1)
                printf("\nError: reading data from %s\n",argv[1]);
            
            if(close(srcFD) == -1)
                printf("\nError: closing file %s\n",argv[1]);
        
            if(close(destFD) == -1)
                printf("\nError: closing file %s\n",argv[3]);
            break;

        default:
            for(int i=1 ;i <argc ;i++){
                srcFD=open(argv[i], O_RDONLY);
                if(srcFD==-1){
                    printf("\nError: cannot open '%s' : %s\n",argv[i],strerror(errno));
                    exit(EXIT_FAILURE);	
                }
                while((numBytesRead=read(srcFD,buff,BUFF_SIZE))>0) //displaying the content
                    printf("%s",buff);
                printf ("\n");
            }
    }
    return 0;
}