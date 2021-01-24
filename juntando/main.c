#include "baseX.h"

BaseX leitura () {
	BaseX s;
	printf("Insira a base do número: ");
	scanf("%d", &s.base);
  printf("Qual número que deseja converter: ");
	if (s.base == 10) {
		scanf("%lf", &s.decimal);
		decimalToX(&s);
		doubleToX(&s);
	}else {
		//double aux, f;
		//int d;
		//scanf("%lf", &aux);
	}

	return s;
}

void liberaMem (BaseX s) {
	free(s.fracionario.vet);
	free(s.inteiro.vet);
}

int main () {
	BaseX entrada = leitura();
	printNum(entrada.fracionario);
	printf(".");
	printNum(entrada.inteiro);
	printf("\n");
	liberaMem(entrada);

	return 0;
}
