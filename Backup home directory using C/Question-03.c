#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>


char HOMEDEFAULT[]="/home/";
char *homep = NULL;
char *backupPATH;
int main(int argc, char *argv[]){
    char dir[20];
    printf("\nEnter Your user name : ");
    scanf("%s",dir);

    if (getenv("HOME") == NULL)
        homep = getenv("HOME");
    if (homep == NULL)
        homep = strcat(HOMEDEFAULT,dir);
    if (getenv("PWD") == NULL)
        backupPATH = getenv("PWD");
    if (backupPATH == NULL)
        backupPATH = strcat(homep,"/Desktop");
    execlp("cp","cp","-r",homep,backupPATH,NULL);
    printf("\nexeclp() System call Error for \"cp\" : %s\n",strerror(errno));
    return 0;
}