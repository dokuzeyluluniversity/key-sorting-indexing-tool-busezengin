#include <stdio.h>
int main( int argc, const char* argv[] ) {
    FILE *rm;
    char buf[201];

    printf("\r\nUdemy.com - Reading from Files in C\r\n");

    rm = fopen("sample.dat", "r+");
    if (rm != NULL) {
        fread(buf, 1, 200, rm);
        buf[(sizeof buf)-1] = 0;
        printf("%s", buf);
        fclose(rm);
    }
    else
        printf("File Not Found.\r\n");
}