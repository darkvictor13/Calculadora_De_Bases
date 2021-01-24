#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_TAM 50


typedef struct {
	unsigned short int* vet;
	int tam;
}numero;

typedef struct {
	numero fracionario;
	numero inteiro;
	int base;
	int tam;
	double decimal;
}BaseX;

void troca (unsigned short int *a, unsigned short int *b);

// vai trocando do começo e do fim ate chegar no meio
void inverteNumero (numero *n);

/******************************
  * @Pré-condição: num > 1.0
  * Nessa função usa apenas a parte inteira
	* do número contido na struct
*****************************/
void decimalToX (BaseX *r);

void printNum (numero num);

/*void printPolinomio(BaseX num) {
  for(int i = 0; i < num.tam ; i++) {
    printf("(%d * %d^%d)", num.numero[i], num.base, i);
    if (i != 0) {
      printf(" + ");
    }else {
      continue;
    }
  }
}
*/

/******************************
  * @Pré-condição: num < 1.0
  *
*****************************/
void doubleToX (BaseX *r);

#endif
