#include "baseX.h"
#include <math.h>

void troca (unsigned short int *a, unsigned short int *b) {
  unsigned short int aux = *a;
  *a = *b;
  *b = aux;
}

// vai trocando do começo e do fim ate chegar no meio
void inverteNumero (numero *n) {
  int metade = (int)floor(n->tam / 2.0);
  for(int i = 0; i < metade; i++) {
    troca((n->vet + i), (n->vet + n->tam - (i + 1)));
  }
}

/******************************
  * @Pré-condição: num > 1.0
  * Nessa função usa apenas a parte inteira
	* do número contido na struct
*****************************/
void decimalToX (BaseX *r) {
  int i;
  int base = r->base;// reduzir os acessos a memória via ponteiros
	int num = (int)floor(r->decimal);

	if (!num) {
		r->tam = 0;
		r->inteiro.vet = NULL;
	}

  r->inteiro.vet = (unsigned short int*)malloc(MAX_TAM * sizeof(unsigned short int));

  for(i = 0; num; i++) {
    r->inteiro.vet[i] = num % base;
    num /= base;
  }
  r->inteiro.tam = i;
  r->inteiro.vet = (unsigned short int*)realloc(r->inteiro.vet, i * sizeof(unsigned short int));
  inverteNumero(&r->inteiro);
}

void printNum (numero num) {
  for(int i = 0; i < num.tam ; i++) {
    if(num.vet[i] > 9) {
      printf("%c", num.vet[i] - 10 + 'A');
    }else {
      printf("%hu", num.vet[i]);
    }
  }
}

void printBaseX (BaseX num, int eol) {
	if (num.inteiro.vet != NULL) {
		printNum(num.inteiro);
	}else {
		printf("0");
	}

	if (num.fracionario.vet != NULL) {
		printf(".");
		printNum(num.fracionario);
	}
	if (eol) {
		printf("\n");
	}
}

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
void doubleToX (BaseX *r) {

	if (r->decimal - floor(r->decimal) == 0.0) {
		r->tam = 0;
		r->fracionario.vet = NULL;
	}

	int i = 0;
	// alocar memória para representar o número
  r->fracionario.vet = (unsigned short int*)malloc(MAX_TAM * sizeof(unsigned short int));

	//double base = (double)r->base;
	double num = r->decimal - floor(r->decimal);

	for(i = 0; num > FLT_MIN && i < MAX_TAM; i++) {
		num *= r->base;
		r->fracionario.vet[i] = (int)floor(num);
		num -= (double)r->fracionario.vet[i];
	}
	if (i == MAX_TAM) {
		printf("Número não foi representado com total precisão\n");
	}
	r->fracionario.tam = i;
	r->fracionario.vet = (unsigned short int*)realloc(r->fracionario.vet, i * sizeof(unsigned short int));
}
