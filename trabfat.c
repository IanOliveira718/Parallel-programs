#include<stdio.h>
#include<omp.h>
#include<stdbool.h>
#include <stdlib.h>
#include <math.h>


// usar gcc trab1.c -o t1 -fopenmp

#define N 10000


int main(int argc, char* argv[])
{
 int i,n;
 int fac = 1;
 n = atoi(argv[1]);


 #pragma omp parallel for private(i) reduction(*:fac)
    for (i=2; i <= n; i++)
      fac*=i;

 /* end of parallel section */


 printf("fatorial = %d\n ",fac);

return 0;
 //printf("Ultimo val proc: %f\n\n",t1);

 //system("pause");

}
