#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int main (int argc, char * argv[]) {
   
   if(argc != 3){
		printf("\nError: %s required arguments [file] [file]\n",argv[0]);
		return -1;
	}
   int FD1, FD2, maxfd=0, nfds,numBytesRead;
   fd_set readset;
   char *buff[BUFF_SIZE];
   FD1 = open(argv[1], O_RDONLY);
   FD2 = open(argv[2], O_RDONLY);

   if(FD1==-1){
      printf("\nError: cannot open '%s' : %s\n",argv[1],strerror(errno));
      return -1;
   }
   if(FD2==-1){
      printf("\nError: cannot open '%s' : %s\n",argv[2],strerror(errno));
      return -1;
   }

   maxfd=(FD1 > FD2)? FD1 : FD2;

   if ((FD1 < 0) || (FD1 >= FD_SETSIZE) || (FD2 < 0) || (FD2 >= FD_SETSIZE))
      return -1;

   FD_ZERO(&readset);
   FD_SET(FD1, &readset);
   FD_SET(FD2, &readset);

   nfds = select(maxfd+1, &readset, NULL, NULL, NULL);

   if (nfds == -1)
      return -1;
   
   if (FD_ISSET(FD1, &readset)) {
   	printf ("%s fd[%d] is ready for reading and the DATA is : \n",argv[1],FD1);
      while((numBytesRead=read(FD1,buff,BUFF_SIZE))>0)
        if(write(STDOUT_FILENO,buff,numBytesRead) != numBytesRead)
			printf("\nError: writing data to %s\n",argv[1]);
   }
   if (FD_ISSET(FD2, &readset)){ 
   	printf ("%s fd[%d] is ready for reading and the DATA is : \n",argv[2],FD2);
      while((numBytesRead=read(FD2,buff,BUFF_SIZE))>0)
        if(write(STDOUT_FILENO,buff,numBytesRead) != numBytesRead)
			printf("\nError: writing data to %s\n",argv[2]);
   }
   
   if(close(FD1) == -1)
      printf("\nError: closing file '%s'\n",argv[1]);
    
   if(close(FD2) == -1)
      printf("\nError: closing file '%s'\n",argv[2]);
   return 0;
}
