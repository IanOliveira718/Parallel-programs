#include<stdio.h>
#include<omp.h>
#include<stdbool.h>
#include <time.h>
#include <windows.h>

// usar gcc trab1.c -o t1 -fopenmp


#define N 1000
void main(){
 double interval;
 int i,j,k;
 float t,t1;
 bool b1 = false;
 float a[N][N], b[N][N], c[N][N];

 for (i=0; i < N; i++){
  for(j=0; j < N; j++)
  a[i][j] = b[i][j] = i * j * 1.0;
 } 
 

 #pragma omp parallel shared(a,b,c) private(i,j,k) 
 {  

 #pragma omp for
    
    for (i=0; i < N; i++){

      for(j=0; j < N; j++){
        c[i][j] = 0;
        for(k=0; k < N; k++){
          
          c[i][j] = c[i][j] + a[i][k] * b[k][j];
        }
        
      }

      //printf(" (%f) ", c[i]);
      
      
    }
   
    

 } /* end of parallel section */

 //printf("Primeiro val proc: %f\n ",t);
 //printf("Ultimo val proc: %f\n\n",t1);

 system("pause");

}