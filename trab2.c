#include<stdio.h>
#include<omp.h>
#include<stdbool.h>
#include <time.h>
#include <math.h>


// usar gcc trab1.c -o t1 -fopenmp

//#define N 500


int main(int argc,char *argv[])
{
 double mypi,pi,h,sum,x,a;
 int i,n;
 
 n=atoi(argv[1]);
 h= 1.0/(double)n;
 sum = 0.0;

 #pragma omp parallel shared(mypi,h) private(i,x) reduction(+:sum)
 {  

 #pragma omp for
    
    for (i=1; i <= n; i++){
      x = h * ((double)i-0.5);
      sum += 4.0/(1.0 + x*x);
      
    }
   
    

 } /* end of parallel section */

mypi = h * sum;

 printf("pi is aprx %.16f\n ",mypi);

return 0;
 //printf("Ultimo val proc: %f\n\n",t1);

 //system("pause");

}
