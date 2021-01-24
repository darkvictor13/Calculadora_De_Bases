#include "baseX.h"

BaseX leitura () {
	BaseX s;
	int base;
	printf("Insira a base do número: ");
	scanf("%d", &base);
  printf("Qual número que deseja converter: ");
	if (base == 10) {
		scanf("%lf", &s.decimal);
		printf("Deseja transformar para qual base: ");
		scanf("%d", &s.base);
		decimalToX(&s);
		doubleToX(&s);
	}else {
		//lerNum(s.inteiro)
		//lerNum(s.fracionario)

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
	printBaseX(entrada, 1);
	liberaMem(entrada);
	return 0;
}
