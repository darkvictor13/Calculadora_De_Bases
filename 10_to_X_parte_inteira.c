#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TAM 50

typedef struct {
 unsigned short int* numero;
 int base;
 int tam;
}BaseX;

void troca (unsigned short int *a, unsigned short int *b) {
  unsigned short int aux = *a;
  *a = *b;
  *b = aux;
}

// vai trocando do começo e do fim ate chegar no meio
void inverteVet (unsigned short int *vet, int tam) {
  int metade = (int)floor(tam / 2.0);
  for(int i = 0; i < metade; i++) {
    troca((vet + i), (vet + tam - (i + 1)));
  }
}

void decimalToX (int num_decimal, BaseX *r) {
  int i;
  int base = r->base;// reduzir os acessos a memória via ponteiros

  r->numero = (unsigned short int*)malloc(MAX_TAM * sizeof(unsigned short int));

  for(i = 0; num_decimal; i++) {
    r->numero[i] = num_decimal % base;
    num_decimal /= base;
  }
  r->tam = i;
  r->numero = (unsigned short int*)realloc(r->numero, i * sizeof(unsigned short int));
  inverteVet(r->numero, r->tam);
}

void printBaseX (BaseX num) {
  for(int i = 0; i < num.tam ; i++) {
    if(num.numero[i] > 9) {
      printf("%c", num.numero[i] - 10 + 'A');
    }else {
      printf("%hu", num.numero[i]);
    }
  }
}

void printPolinomio(BaseX num) {
  for(int i = 0; i < num.tam ; i++) {
    printf("(%d * %d^%d)", num.numero[i], num.base, i);
    if (i != 0) {
      printf(" + ");
    }else {
      continue;
    }
  }
}

int main () {
  int num;
  BaseX n;
  printf("Qual número que deseja converter? (na base 10)\n--> ");
  scanf("%d", &num);
  printf("Você deseja converter o número para que base?\n--> ");
  scanf("%d", &n.base);

  decimalToX(num, &n);

  printf("O número na base (%d) é = ", n.base);
  printBaseX(n);
  printf("\n");

  printf("%d(base 10) = ", num);
  printPolinomio(n);
  printf("(base %d)\n", n.base);

  free(n.numero);
  n.numero = NULL;
  //printf("num na base 16 = %x\n", num);
  return 0;
}
