#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int FD;
	
	//Condition for arguments
	if(argc < 2)
	{
		printf("\nError: '%s' required arguments [source_file]\n\n",argv[0]);
		exit(EXIT_FAILURE);
	}
 
	//unlink multiple files or user define files
    for(int i=1;i<argc;i++){
	    FD = unlink(argv[i]);
	    if(FD == -1)
		    printf("\nError: cannot remove '%s' : %s\n",argv[i],strerror(errno));
    }
	
	return 0;
}