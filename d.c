#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
json_object_get_int(keyEnd)-
#include <time.h>
#define RECORD_COUNT 10
struct _Person {
	char name[22];
	char ID[10];
	float score1;
	float score2;
	float score3;
};

typedef struct _Person Person;

struct _Index {
	char name[22];
	int index;
	
};
typedef struct _Index Index;

int personNumber;

int comparePersons(const void* a, const void* b){
	return (strcmp(((Index*)a)->name, ((Index*)b)->name));
}

void generateRandomString(char* target, char* dictionary, int maxLength, int minLength){
	int length = minLength + rand()%(maxLength-minLength);
	int dictLength = strlen(dictionary);
	int i;
	for(i=0; i<length; i++){
		int dictIdx = rand()%dictLength;
		target[i] = toupper(dictionary[dictIdx]);
	}
		
	target[length] = '\0';
}

void generatePerson(Person* person){
	generateRandomString(person->name, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 22, 5);
	generateRandomString(person->ID,"0123456789",10,9);
	person->score1 = rand()%100;
	person->score2 = rand()%100;
	person->score3 = rand()%100;
}

void generateRandomDataFile(){
	srand(time(NULL));
	FILE* fp;
	fp = fopen("randomdata.dat", "wb");
	if(!fp)
		return;
	Person person[RECORD_COUNT];
	int i;
	for(i=0; i<RECORD_COUNT; i++){
		generatePerson(&person[i]);
	}
		
	printf("Writing %d bytes ", sizeof(Person)*RECORD_COUNT);
		
	fseek(fp, 0, SEEK_SET);
	fwrite(person, sizeof(Person), RECORD_COUNT, fp);
	fclose(fp);

}

void createIndexFile(){
	FILE* fp;
	fp = fopen("randomdata.dat", "rb");
	if(!fp)
		return;
	int i=0;
    Index indexes[10];
	Person data;
	fseek(fp, 0, SEEK_SET);
    fread(&data, sizeof(Person), 1, fp);
    while(!feof(fp)) {
        strcpy(indexes[i].name,data.name);
		indexes[i].index=i;
		i++;
        fread(&data, sizeof(Person), 1, fp);
    }
    qsort(indexes, RECORD_COUNT, sizeof(Index), comparePersons);
	FILE* fp1;
	fp1 = fopen("indexes.dat", "wb");
	if(!fp1)
		return;
	fseek(fp1, 0, SEEK_SET);
	fwrite(indexes, sizeof(Index), RECORD_COUNT, fp1);
	fclose(fp1);
	fclose(fp);
}

int binaryFileSearch(FILE* fp, const char name1[22], int firstIdx, int lastIdx){
	printf("\nRunning Binary Search %d %d\n", firstIdx, lastIdx);
	Index first, last, middle;
	int returnData;
	
	// Calculate the middle Index
	int middleIdx = (firstIdx+lastIdx)/2;

	// Read first record and return if it is the searched one.
	fseek(fp, firstIdx*(sizeof(Index)), SEEK_SET);
	fread(&first, sizeof(Index), 1, fp);
	if(strcmp(first.name,name1) == 0)
	{
		returnData=first.index;
		return returnData;
	}
	// Read last record and return if it is the searched one.
	fseek(fp, lastIdx*sizeof(Index), SEEK_SET);
	fread(&last, sizeof(Index), 1, fp);
	if(strcmp(last.name,name1) == 0)
	{
		returnData=last.index;
		
		return returnData;
	}
	// Recursion exit condition, If middle index is equal to first or last index
	// required comparisons are already made, so record is not found.
	// Create and return an empty person.
	if(middleIdx==firstIdx || middleIdx == lastIdx) {
		int d=-1;
		return d;
	}

	// Read the middle record and return if it is the searched one.
	fseek(fp, middleIdx*sizeof(Index), SEEK_SET);
	fread(&middle, sizeof(Index), 1, fp);
	if(strcmp(middle.name,name1) == 0)
	{
		returnData=middle.index;
		return returnData;
	}
	// Determine the record position and recursively call with appropriate attributes.
	if(strcmp(middle.name,name1)>0) {
		return binaryFileSearch(fp, name1, firstIdx+1, middleIdx-1);
	} 
	else {
		return binaryFileSearch(fp, name1, middleIdx+1, lastIdx-1);
	}
}

int findRecordByName(char name1[22]) {
    // Open the file
    FILE* inputFile;
    inputFile = fopen("indexes.dat", "rb");

    // Calculate initial first and last indexes.
    int firstIdx = 0;
    fseek(inputFile, personNumber*sizeof(Index), SEEK_SET);
    int lastIdx = (ftell(inputFile)/sizeof(Index))-1;

    // Initiate the search.
    int result = binaryFileSearch(inputFile, name1, firstIdx, lastIdx);
    fclose(inputFile);
    return result;
}

void printFile()
{
	printf("personNumber: %d\n", personNumber);
	FILE* inputFile;
    	inputFile = fopen("randomdata.dat","rb");
	fseek(inputFile, 0, SEEK_SET);
	int i;	    
	for(i=0;i<RECORD_COUNT;i++)
        {
		Person bufferPerson;
		fread(&bufferPerson,sizeof(Person),1,inputFile);
		printf("name is %s, id is %s, score1 is:%f \n", bufferPerson.name, bufferPerson.ID, bufferPerson.score1);
		
	}
	fclose(inputFile);
}
void printFile1()
{
	printf("personNumber: %d\n", personNumber);
	FILE* inputFile;
    	inputFile = fopen("indexes.dat","rb");
	fseek(inputFile, 0, SEEK_SET);
	int i;	    
	for(i=0;i<RECORD_COUNT;i++)
        {
		Index bufferPerson;
		fread(&bufferPerson,sizeof(Index),1,inputFile);
		printf("name is %s, index is %d \n", bufferPerson.name, bufferPerson.index);
		
	}
	fclose(inputFile);
}


void printMenu(int* answer){

	//print the user menu
	printf("You can perform the following tasks: \n");
	printf("(1) Generate Sorted Random Data File \n");
	printf("(2) Find Record by Name \n");
	printf("(3) Create Indexes \n");
	printf("(4) List File Data \n");
	printf("-------------------------------------\n");
	printf("(5) Quit \n");
	printf("Please Select one... \n");
	scanf("%d",answer);
}

int main(){

	int answer;
	int who;
	personNumber = RECORD_COUNT;
	
	ab:
        
	//print the user menu and read user answer
	printMenu(&answer);

	while(answer>5 || answer<1)
	{
		printf("\nEnter a valid choice by pressing ENTER key again");
		printMenu(&answer);
	}

	switch(answer)
	{
		case 1: generateRandomDataFile();
			printFile();
			goto ab;
			break;
		case 2: printf("Enter the name that you want to search :");
			char name1[22];
			scanf("%s", name1);
            printf("%s",name1);
			who = findRecordByName(name1);
            printf("Was the index found?");
            printf(" %d",who);
			FILE* file1;
    	    file1 = fopen("randomdata.dat","rb");
            if(who >-1){
				fseek(file1, who*sizeof(Person), SEEK_SET);
				Person data;
				fread(&data, sizeof(Person), 1,file1);
				printf("\n---Person of interest--- \n name is: %s \n score1 is: %lf score2 is %lf score3 is %lf\n", data.name, data.score1,data.score2,data.score3);
            }
            else 
				printf("Not found...");
            goto ab;
			break;
		case 3: createIndexFile();
			goto ab;
            break;
		case 4: printf("List of the sorted File \n");
			printFile1();
            goto ab;
			break;				
		case 5: printf("Program is terminating \n");
			break;
	}

}