#include<stdio.h>
#include<stdlib.h>

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

int main(){
  int n1, m1, n2, m2;
  printf("Enter Shape of matrix 1:");
  scanf("%d %d", &n1, &m1);
  printf("Enter Shape of matrix 2:");
  scanf("%d %d", &n2, &m2);
  int* M1 = (int *)calloc(sizeof(int),n1*m1);
  int* M2 = (int *)calloc(sizeof(int),n2*m2);
  int* M3 = (int *)calloc(sizeof(int),n1*m2);
  if(m1 != n2){
    printf("Error. Incompatible dimensions for multiplication.\n");
    return(0);
  }
  printf("Enter first matrix:\n");
  read(M1, n1, m1);

  printf("Enter second matrix:\n");
  read(M2, n2, m2);

  for(int i =0; i < n1; i++){
    for(int j=0; j < m2; j++){
      for(int k=0; k< n2; ++k){
        // M3[i][j] += M1[i][k] * M2[k][j]
        M3[(m2*i + j)] += M1[(i*m1 + k)] * M2[(m2*k + j)];
      }
    }
  }

  disp(M3, n1, m2);
  return 0;

}
