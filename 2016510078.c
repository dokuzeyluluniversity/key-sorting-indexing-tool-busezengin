#include <string.h>
#include <stdio.h>
#include <json/json.h>
//json data names
struct json_object *parsed_json;
struct json_object *dataFileName;
struct json_object *indexFileName;
struct json_object *recordLength;
struct json_object *keyEncoding;
struct json_object *keyStart;
struct json_object *keyEnd;
struct json_object *order;
int main ( int argc, char *argv[] )
{   argv[1]=strcat(argv[1],".json");/*adding .json extension to user's entered input file*/
    
    if ( argc != 2 ) /* argc should be 2 for ./a.out and filename.txt */
    {
        printf( "Please enter a json file" );
    }
    else 
    {
        FILE *file = fopen(argv[1], "rb" );/*read from user's entered json file*/
        char buffer[1024];
        //the file reading process begins
        
        fread(buffer, 1024, 1, file);//get the file inside buffer
	    fclose ( file );
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
            
        }
        else
        {
            perror ( argv[1] ); /* why didn't the file open? */ /*gives error message*/
        }
    }
}