#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>

void breadth_first_order(const char *dir)
{
    struct dirent *direntp;
    struct stat buff;
    int cd,err;
    DIR *dirp=opendir(dir);
    if (!dirp)
    {
        if (errno == ENOENT)
            perror("Directory doesn't exist");
        else
            perror("Unable to read directory");
        exit(EXIT_FAILURE);
    }
    cd=chdir(dir);
    if(cd==-1){
        perror("Error: Failed to change Directory ");
        exit(EXIT_FAILURE);
    }

    while ( NULL != (direntp = readdir(dirp))){
        //If hidden files or current directory and previous directory  are found we continue
        if (direntp->d_name[0] == '.')
            continue;
        printf("%s\n",direntp->d_name);
    }
    rewinddir(dirp);
    while ( NULL != (direntp = readdir(dirp))){
        //If hidden files or current directory and previous directory  are found we continue
        if (direntp->d_name[0] == '.')
            continue;
        err=stat(direntp->d_name,&buff);
        if (err==-1){
            perror("\nError stat system call ");
            exit(EXIT_FAILURE);
        }
        if(S_ISDIR(buff.st_mode)){
            breadth_first_order(direntp->d_name);
            cd=chdir("..");
            if(cd==-1){
                perror("Error: Failed to change Directory ");
                exit(EXIT_FAILURE);
            }
        }
    }
    printf("\n"); 
    if(closedir(dir)==-1)
        printf("Error: Closing Director: %s",dir);   
}
int main(int argc, const char *argv[])
{   
    if(argc != 2){
        printf("\nError: %s required argument [Path]\n\n",argv[0]);
		exit(EXIT_FAILURE);
    }
    breadth_first_order(argv[1]);
    printf("\n");
    return 0;
}


