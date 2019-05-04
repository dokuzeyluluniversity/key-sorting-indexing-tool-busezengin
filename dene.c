    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
     
    int main(void) {
    	char ch;
    	int i = 0;
    	char *dam = calloc(5, sizeof(char)); 
    	/* dam - dynamically allocated memory */
    	while((ch = getchar()) != EOF)
    		dam[i++] = ch;
    	dam[i] = '\0';
    	printf("%s", dam);
    	return 0;
    }