// Name: Maddie Waldie
// Date: 4/26/23
// Title: Lab4 – Step 5
// Description: implements matrix multiplication in a multi-threaded environment

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// N, M, L - global variables
int N, M, L;

//A, B, C matrices
double **matrixA, **matrixB, **matrixC;

struct d {
  int row;
  int col;
};

// Function prototypes
void initializeMatrix(int r, int c, double **matrix);
void *multiplyRow(void* arg);
void printMatrix(int r, int c, double **matrix);

int main(int argc,char *argv[]) //read N, M, and L as command-line arguments
{
    if(argc!=4){
        printf("Usage: %s <N><M><L> \n",argv[0]);
        exit(1);
    }
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    L = atoi(argv[3]);
    int i,j,k=0;
    matrixA = (double **)malloc(sizeof(double *) * N);
    for(i=0;i<N;i++){
        matrixA[i] = (double *)malloc(M);}
    
    matrixB = (double **)malloc(sizeof(double *) * M);
    for(i=0;i<M;i++){
        matrixB[i] = (double *)malloc(L);}

    matrixC = (double **)malloc(sizeof(double *) * N);
    for(i=0;i<N;i++){
        matrixC[i] = (double *)malloc(L);
        }

    pthread_t threads[N*L];
    initializeMatrix(N,M,matrixA);
    initializeMatrix(M,L,matrixB);

    struct d *data;
//create n threads 
    for(i=0; i <N; i++){
        for(j=0;j<L;j++){
            data = (struct d * )malloc(sizeof(struct d));
            data->row =i;
            data->col = j;
            pthread_create(&threads[i*L + j],NULL,multiplyRow,data);
        }
    }
    // wait on children 
    for(k=0;k<N;k++){
        pthread_join(threads[k],NULL);

    }
    //print matrix 
    printf("Printing matrix A:  \n");
    printMatrix(N,M,matrixA);

    printf("Printing matrix B:  \n");
    printMatrix(M,L,matrixB);


    printf("Printing matrix C:  \n");
    printMatrix(N,L,matrixC);
    return 0;



}
 void initializeMatrix(int r,int c, double **matrix){
    srand(time(NULL));
    int i,j;
    for(i=0;i<r;i++)
    {
        for(j =0; j <c; j++){
            matrix[i][j] = rand()%10;
        }
    }
 } 

 void *multiplyRow(void* arg){
    //mult ith row of matrix a by each col matrix b 
    struct d *data =arg;
    int i,j,k;
    i = data->row;
    j = data->col;
    printf("thread %d mult with %dth row by  col\n", i,j);
    double temp = 0;
    for(k = 0; k <M; k++){
        temp+=matrixA[i][k]*matrixB[k][j];
		matrixC[i][j]=temp;

    }
    pthread_exit(0);
 }

void printMatrix(int r,int c, double **matrix){
    //print matrix
    int i,j;
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            printf("%d ",(int)matrix[i][j]);
        }
        printf("\n");
    }
}
