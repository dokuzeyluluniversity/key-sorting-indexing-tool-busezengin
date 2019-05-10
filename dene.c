#include <string.h>
#include <stdio.h>
#include <json/json.h>

int main ( int argc, char *argv[] )
{   argv[1]=strcat(argv[1],".txt");/*adding .json extension to user's entered input file*/
    int i;
    int j =0;
    int lineNumber =0;
    
    if ( argc != 2 ) /* argc should be 2 for ./a.out and filename.txt */
    {
        printf( "Please enter a json file" );
    }
    else 
    {
        FILE *file = fopen(argv[1], "rb" );/*read from user's entered json file*/
        //the file reading process begins
        if ( file != NULL )
        {
            char line[950]; /* line array */
            
            while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
            { 
                //prints special part of the line
                for(int i=2; i<6; i++){
                   
                   // printf ("%c" ,line[i] ); 
                    j++;
                }
                

                printf("%s",line);
                lineNumber++;
            }
            printf("%d \n",lineNumber);
            fclose ( file );
        }
        
        else
        {
            perror ( argv[1] ); /* why didn't the file open? */ /*gives error message*/
        }
        
    }
}