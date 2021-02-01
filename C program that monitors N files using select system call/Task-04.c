#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>


int main (int argc, char * argv[]) {
   int FD[argc], maxfd=0,nfds;
   fd_set readset;
   if(argc <2 ){
		printf("\nError: %s required arguments [file]...\n",argv[0]);
		return -1;
	}
   FD_ZERO(&readset);
   for(int i=1;i<argc ;i++){
      FD[i] = open(argv[i], O_RDONLY);

      if(FD[i]==-1){
         printf("\nError: cannot open '%s' : %s\n",argv[i],strerror(errno));
         return -1;
      }

      if ((FD[i] < 0) || (FD[i] >= FD_SETSIZE))
         return -1;
      maxfd=(maxfd <= FD[i]) ? FD[i]: maxfd;
      FD_SET(FD[i], &readset);
   }
   nfds = select(maxfd+1, &readset, NULL, NULL, NULL);

   if (nfds == -1)
      return -1;

   for(int i=1;i<argc;i++){
      if (FD_ISSET(FD[i], &readset)) 
   	printf ("%s fd[%d] is ready for reading\n",argv[i],FD[i]);
   
      if(close(FD[i]) == -1)
         printf("\nError: closing file '%s'\n",argv[i]);
   }
   return 0;
}
