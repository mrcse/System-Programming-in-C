#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>

void depth_first_order(const char *dir,int indent)
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
    cd=chdir(dir);      // Change Directory
    if(cd==-1){
        perror("Error: Failed to change Directory ");
        exit(EXIT_FAILURE);
    }

    while ( NULL != (direntp = readdir(dirp)))
    {
        //If hidden files or current directory and previous directory  are found we continue
        if (direntp->d_name[0] == '.')
            continue;
        printf("%*s%s\n",indent,"",direntp->d_name);
        err=stat(direntp->d_name,&buff);
        if (err==-1){
            perror("\nError stat system call ");
            exit(EXIT_FAILURE);
        }
        if(S_ISDIR(buff.st_mode)){
            depth_first_order(direntp->d_name,indent + 4);
            cd=chdir("..");
            if(cd==-1){
                perror("Error: Failed to change Directory ");
                exit(EXIT_FAILURE);
            }
        }
    }
    if (getcwd(mycwd, 255) == NULL)
        perror("Failed to get current working directory");
    if(closedir(dir)==-1)
        printf("Error: Failed to close Directory '%s'\n",mycwd);  
}
int main(int argc, const char *argv[])
{   
    int indent=0;
    if(argc != 2){
        printf("\nError: %s required argument [Path]\n\n",argv[0]);
	exit(EXIT_FAILURE);
    }
    depth_first_order(argv[1],indent);
    printf("\n");
    return 0;
}
