#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define THREADS_MAX 4


struct params {
	int *A, *B, *C;
	int m, n, k, start_row, end_row;
};


// display matrix M dim: [m, n]
void disp(int * M, int n, int m);

// process to be executed by a thread. 
void *proc(void * arg);


// read values into an array from STDIN
void read(int * M, int n, int m);

int main(int argc, char const *argv[])
{
	int n, m, k;
	int *A, *B, *C;
	
	printf("Enter the values for dimensions N, M, K:\n (A:NxM and B:MxK)\n");
	scanf("%d %d %d", &n, &m, &k);

	A = (int *)calloc(sizeof(int), n*m);
	B = (int *)calloc(sizeof(int), m*k);
	C = (int *)calloc(sizeof(int), n*k);

	printf("Enter values of first matrix\n");
	read(A, n, m);
	printf("Enter values of second matrix\n");
	read(B, m, k);

	disp(A, n, m);
	disp(B, m, k);

	int row = 0; // decides h
	int threads = THREADS_MAX;
	pthread_t tid[THREADS_MAX];

	while(threads && row<n){

		struct params * p = (struct params*)malloc(sizeof(struct params));
		p->A = A;
		p->B = B;
		p->C = C;
		p->n = n;
		p->m = m;
		p->k = k;
		p->start_row = row;
		p->end_row = row + (n-row)/threads; 

		row = p->end_row;
		threads--;

		pthread_create(tid+threads, NULL, proc, (void*)p);
		// printf("%d %d\n", p->start_row, p->end_row);

		// pthread_t tid;
		// pthread_attr_t attr;
		// pthread_attr_init(&attr);
		
	}
	// exit(0);
	for (int i = 0; i < THREADS_MAX; ++i)
	{
		pthread_join(tid[i], NULL);
	}

	disp(C, n, k);
	return 0;
}

void disp(int * M,int n,int m){
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      printf("%d\t", M[(m*i + j)]);
    }
    printf("\n" );
  }
}

void read(int * M, int n, int m){
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      scanf("%d", M + (m*i + j));
    }
  }
}

void *proc(void * p){
	struct params* par = (struct params*) p;
	for(int row=par->start_row; row<par->end_row; ++row){
		for(int col=0; col<par->k; ++col){
			for(int i=0; i<par->m; ++i){
				// C[row][col] += A[row][j] * B[j][col]
				par->C[row*par->k + col] += par->A[row*par->m + i] * par->B[i*par->k+col];
			}
		}
	}
	free(par);
	par = NULL;
	pthread_exit(NULL);
	// return NULL;
}