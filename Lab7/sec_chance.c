#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int pageno;
    int second_chance;
} ref_page;


int main(int argc, char *argv[]) {
	int cacheSize = atoi(argv[1]); 
    ref_page cache[cacheSize]; 
    char pageCache[100]; 

    int counter =0;
    int i, j;
    int totalFaults = 0; 
    int totalRequests = 0;
    int placeInArray = 0;
    
    for (i = 0; i < cacheSize; i++) { 
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)) {
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        bool foundInCache = false;
        totalRequests++;

		for(i = 0; i < cacheSize; i++) {
			if(cache[i].pageno == page_num) {
				if(cache[i].second_chance == 0)
					cache[i].second_chance = 1;
				break;
			} else if(i == cacheSize-1) {
				printf("Page %d caused a fault\n", page_num);   
				totalFaults++;
				for(j = counter; j < cacheSize; j++) {
					if(cache[j].second_chance == 1) {
						cache[j].second_chance = 0;
						counter++;
						if(counter == cacheSize) {
							counter = 0;
							j = -1;
						}
					} else {
						cache[j].pageno = page_num;
						cache[j].second_chance = 0;
						counter++;
						if(counter == cacheSize) {
							counter = 0;
						}
						break;
					}
				}
			}
		}
    }

    double hitRate = (double)(totalRequests - totalFaults) / (double)totalRequests;

    printf("%d Total Page Requests\n", totalRequests);
    printf("%d Total Page Faults\n", totalFaults);  
    printf("%f Total Hit Rate\n", hitRate);

    return 0;
}