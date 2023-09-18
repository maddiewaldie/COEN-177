// Name: Maddie Waldie
// Date: 5/3/23
// Title: Lab7 – Step 1
// Description: Generate a file for the test input

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
 
int main(int argc, char *argv[]) {
    int capNumber = atoi(argv[2]);
    int someNumber = atoi(argv[1]);
    FILE *fp;
    char buffer [someNumber];
    int i;
    fp = fopen("testInput.txt", "w");
    for (i=0; i<someNumber; i++){
        sprintf(buffer, "%d\n", rand()%capNumber);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}