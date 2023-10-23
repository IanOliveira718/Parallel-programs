#include<stdio.h>
#include<omp.h>
#include<stdbool.h>
#include <stdlib.h>
#include <math.h>


// usar gcc trab1.c -o t1 -fopenmp

#define N 10000


int main()
{
 int i,max,a[N];
 


 #pragma omp parallel for private(i) shared(a,max) 
    for (i=0; i < N; i++)
      a[i]= rand();

 /* end of parallel section */


max=a[0];
 #pragma omp parallel for private(i) shared(a,max)
    for (i=1; i < N; i++)
      if(a[i]>max)
        #pragma omp critical
            if(a[i]>max) max = a[i];
       
 /* end of parallel section */



 /* end of parallel section */



 printf("max = %d\n ",max);

return 0;
 //printf("Ultimo val proc: %f\n\n",t1);

 //system("pause");

}
