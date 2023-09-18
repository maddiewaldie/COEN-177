#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {     
        int pageno;
        int age;
} ref_page;

int main(int argc, char *argv[]) {
    int cacheSize=atoi(argv[1]);
    ref_page cache[cacheSize]; 
    char pageCache[100]; 
    int cacheIndex=0;
    int totalFaults=0; 
    int totalRequests=0;
    int i, j, k, page_num, oldest;
    
    for(i=0;i<cacheSize;i++) {
        cache[i].pageno = -1;
        cache[i].age = 0;
    }

    while(fgets(pageCache, 100, stdin)) {
        page_num = atoi(pageCache);
        totalRequests++;
        oldest = cache[i].age;
        for(i = 0; i < cacheSize; i++) {
            if(cache[i].pageno == page_num) {
                for(j = 0; j < cacheSize; j++) {                           
                    if(cache[j].age < cache[i].age) {
                        cache[j].age++;
                    }
                }
                cache[i].age = 0;
                break;
            }
            else if(i == cacheSize-1) {
                printf("Page %d caused a fault\n", page_num);           
                totalFaults++;  
                for(j = 0; j < cacheSize; j++) {
                    cache[j].age++;
                }
                
                for(k = 0; k < cacheSize ; k++) {
                    if(oldest < cache[k].age) {
                        oldest = cache[k].age;
                        cacheIndex = k;
                    }
                }
                cache[cacheIndex].pageno = page_num;
                cache[cacheIndex].age = 0;
            }
        }
    }

    double hitRate = (double)(totalRequests - totalFaults) / (double)totalRequests;

    printf("%d Total Page Requests\n", totalRequests);
    printf("%d Total Page Faults\n", totalFaults);  
    printf("%f Total Hit Rate\n", hitRate);

    return 0;
}