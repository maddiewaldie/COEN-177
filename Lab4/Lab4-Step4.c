// Name: Maddie Waldie
// Date: 4/26/23
// Title: Lab4 – Step 4
// Description: implements matrix multiplication in a multi-threaded environment

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// N, M, L - global variables
int N, M, L;

//A, B, C matrices
double **matrixA, **matrixB, **matrixC;

// Function prototypes
void initializeMatrix(int r, int c, double **matrix);
void *multiplyRow(void* arg);
void printMatrix(int r, int c, double **matrix);

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Usage: %s <N> <M> <L> \n", argv[0]);
		exit(1);
	}
	N = atoi(argv[1]);
	M = atoi(argv[2]);
	L = atoi(argv[3]);

	int i, j, k = 0;

	matrixA = (double **)malloc(sizeof(double *) *N);
	for (i = 0; i < N; i++) {
		matrixA[i] = (double *)malloc(M);
	}

	matrixB = (double **)malloc(sizeof(double *) *M);
	for (i = 0; i < M; i++) {
		matrixB[i] = (double *)malloc(L);
	}

	matrixC = (double **)malloc(sizeof(double *) *N);
	for (i = 0; i < N; i++) {
		matrixC[i] = (double *)malloc(L);
	}

	// N threads
	pthread_t threads[N];

	// Initialize matrix A
	initializeMatrix(N, M, matrixA);
	// Initialize matrix B
	initializeMatrix(M, L, matrixB);

	//creating N threads, each multiplying ith row of matrixA by each column of matrixB to produce the row of matrixC
    for(i=0;i<N;i++) {
        pthread_create(&threads[i],NULL,multiplyRow,(void*)(size_t)i);
    }

	// Main thread waits for child threads to complete
	for(i=0;i<N;i++){
		pthread_join(threads[i],NULL);
	}

	// Print Matrix A, B, and C
	//Print Matrix A
	printf("Printing Matrix A: \n");
	printf("\n");
	printMatrix(N, M, matrixA);
	printf("\n");
	//Print Matrix B
	printf("Printing Matrix B: \n");
	printf("\n");
	printMatrix(M, L, matrixB);
	printf("\n");
	//Print Matrix C
	printf("Printing Matrix C: \n");	
	printf("\n");
	printMatrix(N, L, matrixC);
	return 0;
}

//initialize matrix with random values
void initializeMatrix(int r,int c, double **matrix) {
    srand(time(NULL));
	int i, j;
	for(i = 0; i < r; i++){
		for (j = 0; j < c; j++){
			matrix[i][j] = rand() % 10;
		}
	}
	return;
}

//print matrix
void printMatrix(int r,int c, double **matrix) {
    int i, j;
	for(i=0;i<r;i++){
		for(j=0;j<c;j++)
			printf("%d ",(int) matrix[i][j]);
		printf("\n");
	}
}

//thread multiply function
void *multiplyRow(void* arg) {
    int i, j, k;
	// Thread multiplying the ith row of matrix by each column
	i = (int)(unsigned long)(size_t *)arg;
	for(j=0; j < L; j++) {
		double temp = 0;
		for(k = 0; k < M; k++) {
			temp += matrixA[i][k] * matrixB[k][j];
		}
		matrixC[i][j] = temp;
	}
	pthread_exit(0);
}
