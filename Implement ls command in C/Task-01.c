#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>

struct stat buff;

void permissions(int r,int w ,int x){
    if(r & buff.st_mode)
        printf("r");
    else
        printf("-");
    if(w & buff.st_mode)
        printf("w");
    else
        printf("-");
    if(x & buff.st_mode)
        printf("x");
    else
        printf("-");
                
}

void ls(const char *dir,int op_l)
{
    struct dirent *direntp;
    int err;
    char *timep,*USR,*GRP;
    DIR *dirp = opendir(dir);
    if (!dirp)
    {
        if (errno == ENOENT){
            //If the directory is not found
            perror("Directory doesn't exist");
        }else{
            //If the directory is not readable then throw error and exit
            perror("Unable to read directory");
        }
        exit(EXIT_FAILURE);
    }
    if(op_l)
        printf("total (?)\n");
    while ( NULL != (direntp = readdir(dirp)))
    {
        //If hidden files are found we continue
        if (direntp->d_name[0] == '.')
            continue;
        //If user enter -l opetion
        err=stat(direntp->d_name,&buff);
        if (err==-1){
            perror("\nError stat system call ");
            exit(EXIT_FAILURE);
        }
        if(op_l){
            if(S_ISDIR(buff.st_mode))
                printf("d");
            else
                printf("-");

            permissions(S_IRUSR,S_IWUSR,S_IXUSR);
            permissions(S_IRGRP,S_IWGRP,S_IXGRP);
            permissions(S_IROTH,S_IWOTH,S_IXOTH);

            USR=getpwuid(buff.st_uid)->pw_name;
            GRP=getpwuid(buff.st_gid)->pw_name;
            timep=ctime(&buff.st_mtime);
            for(int i=0;*(timep+i)!='\0';i++)
                if(*(timep+i)=='\n')    
                    *(timep+i)='\0';
            
            printf(" %d %s %s %6ld %s %s\n",buff.st_nlink,USR,GRP,buff.st_size,timep,direntp->d_name);
            }else
                printf("%s  ", direntp->d_name);
    }
    if(closedir(dir)==-1){
        perror("Error while closing directory '%s' ",dir);
        exit(EXIT_FAILURE);
    }
}
int main(int argc, const char *argv[])
{
    if (argc == 1)
    {
        ls(".",0);
    }
    else if (argc == 2)
    {
        if (argv[1][0] == '-')
        {
            //Checking if option is passed
            int op_l = 0;
            char *p = (char*)(argv[1] + 1);
            while(*p){
                if(*p == 'l') 
                    op_l = 1;
                else{
                    perror("Option not available");
                    exit(EXIT_FAILURE);
                }
                p++;
            }
            ls(".",op_l);
        }
    }
    printf("\n");
    return 0;
}


