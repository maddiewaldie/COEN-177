#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    char buffer[atoi(argv[2])];
    FILE *fp;
    FILE *fw;
    fp = fopen(argv[1], "rb");
    fw = fopen("writeFile.txt", "wb");
    while (fread(buffer, sizeof(buffer), 1, fp)){
        fwrite(buffer, 1, sizeof(buffer), fw);
    }
    fclose(fp);
    fclose(fw);
}