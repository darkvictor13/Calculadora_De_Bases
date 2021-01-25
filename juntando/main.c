#include "baseX.h"

int main () {
	int is_decimal;
	BaseX entrada = leitura(&is_decimal);
	if (is_decimal) {
		printf("Número na base %d = ", entrada.base);
		printBaseX(entrada, 1);
	}else {
		// .* define a quantidade de casas depois do . a serem impressas
		printf("Número na base 10 = %.*lf\n", entrada.fracionario.tam, entrada.decimal);
	}
	liberaMem(entrada);
	return 0;
}
