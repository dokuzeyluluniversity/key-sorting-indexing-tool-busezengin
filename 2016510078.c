#include <string.h>
#include <stdio.h>
int main ( int argc, char *argv[] )
{   argv[1]=strcat(argv[1],".txt");
    
    if ( argc != 2 ) /* argc should be 2 for ./a.out and filename.txt */
    {
        printf( "usage: %s is provided,filename is not provided", argv[0] );
    }
    else 
    {
        FILE *file = fopen(argv[1], "rb" );
        if ( file == 0 )
        {
            printf( "Could not open file\n" );
        }
        else 
        {
            int x;
            while  ( ( x = fgetc( file ) ) != EOF )
            {
                printf( "%c", x );
            }
            fclose( file );
        }
    }
}