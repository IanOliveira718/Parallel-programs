/*

 
 Propósito:
     Este programa usa um algoritmo de Monte Carlo para calcular PI como um
     exemplo de como geradores de números aleatórios são usados para resolver problemas.
 
 Compilação:
    Este programa precisa que os 3 arquivos: pi_mc.c random.c e random.h estejam no mesmo diretorio
    Para compilar esse programa, é preciso compilar também o programa random.c que contém a definição da função drandom().
     O comando de compilação então é:
 > gcc -o executavel pi_mc.c random.c


 Uso:
     O programa recebe como parâmetro na linha de comando o número de tentativas
 (num_trials). Quando chamar o executável o valor do número de tentativas deve ser passado.

 Algoritmo:
     A ideia básica por trás do algoritmo é fácil de visualizar. Desenhe um
     quadrado em uma parede. Dentro do quadrado, desenhe um círculo. Agora jogue aleatoriamente
     dardos na parede. Alguns dardos cairão dentro do quadrado. Daqueles,
     alguns cairão dentro do círculo. A probabilidade de pousar dentro
     o círculo ou o quadrado são proporcionais às suas áreas.

     Podemos usar um gerador de números aleatórios para “lançar os dardos” e contar
     quantos "dardos" caem dentro do quadrado e quantos dentro do
     ciclo. A divisão desses dois números nos dá a razão entre suas áreas
     e a partir disso podemos calcular pi.

 Detalhes do algoritmo:
     Suponha que o círculo está centralizado dentro do quadrado. O círculo terá um raio de r e cada lado do quadrado terá área 2*r (ou seja, o diâmetro do
     círculo).

         A(círculo) = pi * r^2
         A(quadrado) = (2*r)*(2*r) = 4*r^2

         ratio = A(círculo)/A(quadrado) = pi/4

     Como a probabilidade (P) de um dardo cair dentro de uma figura (ou seja, o quadrado ou o círculo) é proporcional à área, temos

         ratio = P(círculo)/P(quadrado) = pi/4

     Se eu lançar N dardos calculados por números aleatórios distribuídos uniformemente sobre a área do quadrado

        P(quadrado) = N/N .... ou seja, cada dardo cai no quadrado
        P(círculo) = N(círculo)/N

        ratio = (N(círculo)/N)/(N/N) = N(círculo)/N

     Portanto, para encontrar a área, calculo N "dardos" aleatórios e conto quantos caem dentro do círculo. A equação para um círculo é

        x^2 + y^2 = r^2

     Então eu calculo aleatoriamente "x" e "y" distribuídos uniformemente de -r a r e conto o "dardo" como caindo dentro do ciclo se

        x ^ 2 + y ^ 2 < ou = r

 Resultados:
     Como ponto de referência, os primeiros 7 dígitos do valor verdadeiro de pi
     é 3,141592

*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "random.h"

// gcc pi_mc.c -o pi -fopenmp
// The monte carlo pi program
//

int main ( int argc, char *argv[] )
{
   long i;  long Ncirc = 0;
   double pi, x, y, test;
   double r = 1.0;   // radius of circle. Side of squrare is 2*r
    
    long num_trials;
    
    num_trials = atoi(argv[1]);

   seed(-r, r);  // The circle and square are centered at the origin

#pragma omp parallel for private (i)
   for(i=0;i<num_trials; i++)
   {
      x = drandom(); 
      y = drandom();

      test = x*x + y*y;

      if (test <= r*r){
         #pragma omp critical
            if (test <= r*r) Ncirc++;
        }

    }

    pi = 4.0 * ((double)Ncirc/(double)num_trials);

    printf("\n %ld trials, pi is %lf \n",num_trials, pi);

    return 0;
}
	  





