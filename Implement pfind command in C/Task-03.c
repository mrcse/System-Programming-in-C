#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
int flag=0;
void pfind(const char *dir,const char *fileName){
    struct dirent *direntp;
    struct stat buff;
    char mycwd[255];
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

    while ( NULL != (direntp = readdir(dirp)))
    {
        //If hidden files or current directory and previous directory  are found we continue
        if (direntp->d_name[0] == '.')
            continue;
        if((strcmp(direntp->d_name,fileName))==0){
            if (getcwd(mycwd, 255) == NULL)
                    perror("Failed to get current working directory");
            printf("\nFile Found in Directory : %s\n",mycwd);
            flag=1;
        }
        err=stat(direntp->d_name,&buff);
        if (err==-1){
            perror("\nError stat system call ");
            exit(EXIT_FAILURE);
        }
        if(S_ISDIR(buff.st_mode)){
            pfind(direntp->d_name,fileName);
            cd=chdir("..");
            if(cd==-1){
                perror("Error: Failed to change Directory ");
                exit(EXIT_FAILURE);
            }
        }
    }
    if (getcwd(mycwd, 255) == NULL)
        perror("Failed to get current working directory");
    if(closedir(dirp)==-1)
        printf("Error: Failed to close Directory '%s'\n",mycwd);    
}
int main(int argc, const char *argv[])
{   
    if(argc != 3){
        printf("\nError: %s required arguments [Path] [File]\n\n",argv[0]);
	exit(EXIT_FAILURE);
    }
    pfind(argv[1],argv[2]);
    if(flag==0)
        printf("Error: File Not Found\n");
    printf("\n");
    return 0;
}
