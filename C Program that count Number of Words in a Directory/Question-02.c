#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
int WCarray[100]={0};
int count=0;
char *name="";
int toralWordsInDirectory=0;
void ls(const char *dir)
{
	//Here we will list the directory
	struct dirent *d;
    int greater=0;
	DIR *dh = opendir(dir);
	if (!dh){
	    perror("Unable to read directory");
		exit(-1);
	}
	//While the next entry is not readable we will print directory files
	while ((d = readdir(dh)) != NULL)
	{
		//If hidden files are found we continue
		if (d->d_name[0] == '.')
			continue;
        
		// printf("%s  %d\t", d->d_name,wc(d->d_name));
        // printf("\n");
        int temp=wc(d->d_name);
        toralWordsInDirectory+=temp;
        WCarray[count]=temp;
        if(greater<temp)
        {
            greater=temp;
            name=d->d_name;
        }
        count++;
	}
	//printf("\n");
}
int wc(char *f){
    FILE *file;
    int wordCount = 0;
    int isInsideWord = 0;
      wordCount = 0;
      file = fopen(f, "r");
      if (file){
        const size_t line_size = 400;
        char* readLine = malloc(line_size);
        while (fgets(readLine, line_size, file) != NULL){
              for (int i = 0; i < strlen(readLine); i++){
                  if(!isspace(readLine[i])){
                      isInsideWord = 1;
                  }
                  else{
                     if (isInsideWord){
                        isInsideWord = 0;
                        wordCount++;
                     }
                  }
              }
          }
          if(wordCount==0 && isInsideWord==1){
            wordCount = 1;
          }
          fclose(file);
      }
    return (wordCount >0)?wordCount+1:wordCount;
}
void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
  
// A function to implement bubble sort  
void bubbleSort(int arr[], int n)  
{  
    int i, j;  
    for (i = 0; i < n-1; i++)      
      
    // Last i elements are already in place  
    for (j = 0; j < n-i-1; j++)  
        if (arr[j] > arr[j+1])  
            swap(&arr[j], &arr[j+1]);  
} 
int main(int argc, const char *argv[])
{
	ls(".");
    bubbleSort(WCarray,count);
    printf("\n\t\tWords Count Array \n\nArray :");
    for(int i=0;i<count;i++)
        printf("%d\t",WCarray[i]);
    printf("\nTotal Number of Words in this Directory is : %d\n\n",toralWordsInDirectory);
    printf("\nReported File in This Directory : %s\n\n",name);
    
	return 0;
}