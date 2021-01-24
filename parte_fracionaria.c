#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_TAM 50

typedef struct {
 unsigned short int* numero;
 int base;
 int tam;
}BaseX;

/******************************
  * @Pré-condição: num < 1.0
  *
*****************************/
void doubleToX (double num, BaseX *r) {
	int i = 0;
	// alocar memória para representar o número
  r->numero = (unsigned short int*)malloc(MAX_TAM * sizeof(unsigned short int));

	//double base = (double)r->base;

	for(i = 0; num > FLT_MIN && i < MAX_TAM; i++) {
		num *= r->base;
		r->numero[i] = (int)floor(num);
		num -= (double)r->numero[i];
	}
	if (i == MAX_TAM) {
		printf("Número não foi representado com total precisão\n");
	}
	r->tam = i;
	r->numero = (unsigned short int*)realloc(r->numero, i * sizeof(unsigned short int));
}

void printBaseX (BaseX num) {
	printf("0.");
  for(int i = 0; i < num.tam ; i++) {
    if(num.numero[i] > 9) {
      printf("%c", num.numero[i] - 10 + 'A');
    }else {
      printf("%hu", num.numero[i]);
    }
  }
}

int main () {
	double n;
  BaseX num;
	printf("Entre com um número double: ");
	scanf("%lf", &n);
	n -= floor(n);
  printf("Você deseja converter o número para que base?\n--> ");
  scanf("%d", &num.base);

	doubleToX(n, &num);

  printf("O número na base (%d) é = ", num.base);
  printBaseX(num);
  printf("\n");

  free(num.numero);
  num.numero = NULL;
  return 0;

	return 0;
}
