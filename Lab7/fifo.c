#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
	int cacheSize = atoi(argv[1]); // Size of Cache from user
    ref_page cache[cacheSize]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // Keeps track of the total page faults
    int totalRequests = 0;
    int placeInArray = 0;
    
    for (i = 0; i < cacheSize; i++) {
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)) {
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        bool foundInCache = false;
        totalRequests++;

        for (i=0; i<cacheSize; i++) {
            if (cache[i].pageno == page_num) {
                foundInCache = true;
                break; // Break out loop because found page_num in cache  
            }
        }   
        if (foundInCache == false) {
            cache[placeInArray].pageno = page_num;
            printf("Page %d caused a fault\n", page_num);   
            totalFaults++;
            placeInArray = (placeInArray + 1) % cacheSize; // Need to keep the value within the cacheSize
        }
    }

    double hitRate = (double)(totalRequests - totalFaults) / (double)totalRequests;

    printf("%d Total Page Requests\n", totalRequests);
    printf("%d Total Page Faults\n", totalFaults);  
    printf("%f Total Hit Rate\n", hitRate);

    return 0;
}