#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
 
#define BUFF_SIZE 1024
 
int main(int argc, char* argv[])
{
	int srcFD,destFD,numBytesRead,nbwrite;
	char *buff[BUFF_SIZE];
	
	if(argc != 3)
	{
		printf("\nError: '%s' required arguments [source] [destination]\n\n",argv[0]);
		exit(EXIT_FAILURE);
	}
 
	//Open source file READ_ONLY
	srcFD = open(argv[1],O_RDONLY);
 
	if(srcFD == -1)
	{
		printf("\nError: cannot open '%s' : %s\n",argv[1],strerror(errno));
		exit(EXIT_FAILURE);	
	}
	
	
	destFD = open(argv[2],O_WRONLY | O_CREAT | O_EXCL, S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH);
 
	if(destFD == -1)
	{
		printf("\nError: cannot open '%s' : %s\n",argv[2],strerror(errno));
		exit(EXIT_FAILURE);
	}
 
	//Start data transfer from src file to dest file till EOF
	while((numBytesRead = read(srcFD,buff,BUFF_SIZE)) > 0)
		if(write(destFD,buff,numBytesRead) != numBytesRead)
			printf("\nError: writing data to %s\n",argv[2]);
	
	if(numBytesRead == -1)
		printf("\nError: in reading data from %s\n",argv[1]);
 
	if(close(destFD) == -1)
		printf("\nError: closing file %s\n",argv[2]);
	
	srcFD = unlink(argv[1]);
	
	if(srcFD == -1)
		printf("\nError: cannot remove '%s' : %s\n",argv[1],strerror(errno));

 
	return 0;
}