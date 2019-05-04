#include <stdio.h>
#include <string.h>
int main(){
    FILE* inputFile;
    char ch[1000];
    char fileName[50];
    printf("Please enter the file name: ");
    scanf("%s",&fileName);
    
    inputFile=fopen(strcat(fileName,".txt"),"r");
    while(!feof(inputFile)){
        fgets(ch,3,inputFile);
        puts(ch);
    }
    fclose(inputFile);
    return 0;
}