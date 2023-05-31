#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

char *buffer;
char *strname;

void* write_func(void* arg) { 
      FILE *wp;
      FILE *fp = fopen(strname, "rb");

      char arr[30];
      sprintf(arr,"%s.sout%d",strname,(int)arg);

      wp = fopen(arr, "wb");
    
      while (fread(buffer, sizeof(buffer), 1, fp)){
          fwrite(buffer,sizeof(buffer),1, wp);
      }
      fclose(wp);
}

int main(int argc, char *argv[]) { 
      buffer = malloc(atoi(argv[2]));
      pthread_t threads[atoi(argv[3])];
      static int i;
      strname = argv[1];

      for (i = 0; i < atoi(argv[3]); i++){
          pthread_create(&threads[i], NULL, write_func, (void *)(size_t)i);
      }
      for (i = 0; i < atoi(argv[3]); i++) {
         pthread_join(threads[i],NULL);
      }
      return 0;
}