#include <string.h>//string operations
#include <stdio.h>//standart buffered input/output
#include <json/json.h>
#include <stdbool.h> //for Boolean type and values
#include <stdlib.h> //standart library definitions
#include <ctype.h>
#include <time.h>
//json data names
struct json_object *parsed_json;
struct json_object *dataFileName;
struct json_object *indexFileName;
struct json_object *recordLength;
struct json_object *keyEncoding;
struct json_object *keyStart;
struct json_object *keyEnd;
struct json_object *order;


//.dat file struct
struct _Index {
	char info[50];/*the part in file which will be sorted*/
    int index;
};
typedef struct _Index Index;

void printFile1()
{
	FILE* inputFile;
    	inputFile = fopen(json_object_get_string(indexFileName),"rb");
	fseek(inputFile, 0, SEEK_SET);
	int i;	    
	for(i=0;i<100;i++)
        {
		Index bufferPerson;
		fread(&bufferPerson,sizeof(Index),1,inputFile);
		printf("name is %s, index is %d \n", *(bufferPerson).info, bufferPerson.index);
		
	}
	fclose(inputFile);
}
int findRecord(char record[25]) {
    // Open the file
    FILE* inputFile;
    inputFile = fopen(json_object_get_string(indexFileName), "rb");

    // Calculate initial first and last indexes.
    int firstIdx = 0;
    fseek(inputFile, 100*sizeof(Index), SEEK_SET);
    int lastIdx = (ftell(inputFile)/sizeof(Index))-1;

    // Initiate the search.
    int result = binaryFileSearch(inputFile, record, firstIdx, lastIdx);
    fclose(inputFile);
    return result;
}
int binaryFileSearch(FILE* fp, const char record[25], int firstIdx, int lastIdx){
	printf("\nRunning Binary Search %d %d\n", firstIdx, lastIdx);
	Index first, last, middle;
	int returnData;
	
	// Calculate the middle Index
	int middleIdx = (firstIdx+lastIdx)/2;

	// Read first record and return if it is the searched one.
	fseek(fp, firstIdx*(sizeof(Index)), SEEK_SET);
	fread(&first, sizeof(Index), 1, fp);
	if(strcmp(first.info,record) == 0)
	{
		returnData=first.index;
		return returnData;
	}
	// Read last record and return if it is the searched one.
	fseek(fp, lastIdx*sizeof(Index), SEEK_SET);
	fread(&last, sizeof(Index), 1, fp);
	if(strcmp(last.info,record) == 0)
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
	if(strcmp(middle.info,record) == 0)
	{
		returnData=middle.index;
		return returnData;
	}
	// Determine the record position and recursively call with appropriate attributes.
	if(strcmp(middle.info,record)>0) {/* finds in which interval the information*/
		return binaryFileSearch(fp, record, firstIdx+1, middleIdx-1);
	} 
	else {
		return binaryFileSearch(fp, record, middleIdx+1, lastIdx-1);
	}
}
int compareInformation(const void* a, const void* b){
    return (strcmp(((Index*)a)->info, ((Index*)b)->info));
}
void createIndexFile(){
    FILE *file = fopen(json_object_get_string(dataFileName), "rb" );/*read from user's entered json file*/
        int lineNumber=0;
        int indx=0;//index count
        int infoLength = json_object_get_int(keyEnd)-json_object_get_int(keyStart)+1;
        Index indexes[100];
        //the file reading process begins
        if ( file != NULL )
        {
            char line[950]; /* line array */
            
            while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
            { 
                int inf=0;//for string
                //prints special part of the line
                for(int i=json_object_get_int(keyStart); i<=json_object_get_int(keyEnd)+1; i++){
                   indexes[indx].info[inf]=line[i];//creates structs' information
                   
                   inf++;
                }
                indexes[indx].index=indx;
                
                lineNumber++;
                
                indx++;
            }
            qsort(indexes,100, sizeof(Index),compareInformation);
            FILE* indexFile;
            indexFile=fopen(json_object_get_string(indexFileName),"wb");
            if(!indexFile)
                return;
            fseek(indexFile,0,SEEK_SET);
            fwrite(indexes,sizeof(Index),100,indexFile);
            fclose(indexFile);
            fclose ( file );
            printf("Index file is created.");
        }
        
        else
        {
            perror ( json_object_get_string(dataFileName) ); /* why didn't the file open? */ /*gives error message*/
        }
}
void jsonRead(char *argv[]){
        argv[2]=strcat(argv[2],".json");/*adding .json extension to user's entered input file*/
         FILE *file = fopen(argv[2], "rb" );/*read from user's entered json file*/
        char buffer[1024];
        //the file reading process begins
        
        fread(buffer, 1024, 1, file);//get the file inside buffer
	    
        if ( file != NULL )
        {
            parsed_json = json_tokener_parse(buffer);
            //add json names to structs
            json_object_object_get_ex(parsed_json, "dataFileName", &dataFileName);
	        json_object_object_get_ex(parsed_json, "indexFileName", &indexFileName);
	        json_object_object_get_ex(parsed_json, "recordLength", &recordLength);
            json_object_object_get_ex(parsed_json, "keyEncoding", &keyEncoding);
	        json_object_object_get_ex(parsed_json, "keyStart", &keyStart);
            json_object_object_get_ex(parsed_json, "keyEnd", &keyEnd);
	        json_object_object_get_ex(parsed_json, "order", &order);
            //int length=json_object_get_int(keyEnd)-json_object_get_int(keyStart)+1;
            //prints the json file
            printf("dataFileName: %s\n", json_object_get_string(dataFileName));
            printf("indexFileName: %s\n", json_object_get_string(indexFileName));
            printf("recordLength: %d\n", json_object_get_int(recordLength));
            printf("keyEncoding: %s\n", json_object_get_string(keyEncoding));
            printf("keyStart: %d\n", json_object_get_int(keyStart));
            printf("keyEnd: %d\n", json_object_get_int(keyEnd));
            printf("order: %s\n", json_object_get_string(order));
            
            fclose(file);
            
        }
        
        else
        {
            perror ( argv[2] ); /* why didn't the file open? */ /*gives error message*/
        }
        
}
int main ( int argc, char *argv[] )
{   
    
    
    if ( strcmp(argv[1] , "open" )==0) /* for open command */
    {
        jsonRead(argv);//reads the json file and shows it
        
    
    }
    
    if(strcmp(argv[1] , "create_index" )==0){
        
        createIndexFile();//creates index file
        printFile1();//prints the index file
       
    }

    if (strcmp(argv[1] , "search" )==0){
        	char record[22];
            int which;
            which=findRecord(record);
			scanf("%s", record);
            printf("Was the index found?");
            printf(" %d",which);
            FILE* file1;
    	    file1 = fopen(json_object_get_string(indexFileName),"rb");
            if(which >-1){
				fseek(file1, which*sizeof(Index), SEEK_SET);
				Index data;
				fread(&data, sizeof(Index), 1,file1);
				printf("\n---Person of interest--- \n information is: %s \n ", data.info);
            }
            else 
				printf("Not found...");
    }
    
    if (strcmp(argv[1] , "close" )==0){
        free(parsed_json);
        free(dataFileName);
        free(indexFileName);
        free(recordLength);
        free(keyEncoding);
        free(keyStart);
        free(keyEnd);
        free(order);
        printf("Files are closed and memory is freed.")/*Files closed in the functions*/,
    }         
}
