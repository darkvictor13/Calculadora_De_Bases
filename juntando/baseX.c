#include "baseX.h"

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
		return;
	}

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
		return;
	}

	int i = 0;

	double num = r->decimal - floor(r->decimal);
	//printf("Inicio da parte fracionaria = %lf", num);

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


int lerNum(numero *n, char limite) {
	int i;
	char c;
	scanf("%c", &c);
	for(i = 0; c != limite && c != '\n'; i++) {
		if (isdigit(c)) {
			n->vet[i] = (int)(c - '0');
		}else{
			c = toupper(c);
			n->vet[i] = (int)(c - 'A' + 10);
		}
		scanf("%c", &c);
	}
	n->vet = (unsigned short int*)realloc(n->vet, i * sizeof(unsigned short int));
	n->tam = i;
	if (c == '\n') {
		return 1; //leu uma linha completa
	}
	return 0;
}

unsigned short int* alocaNum() {
	return malloc(MAX_TAM * sizeof(unsigned short int));
}

/*
  * A struct numero representa a parte inteira
  *
*/
int xTointeiro(numero n, int base) {
	int soma = 0;
	for(int i = 0; i < n.tam; i++) {
		soma += (n.vet[i] * pow(base, n.tam - 1 - i));
	}
	return soma;
}

/*
  * A struct numero representa a parte fracionaria
  * retorna um valor < 1
*/
double xToDouble(numero n, int base) {
	double soma = (n.vet[0] * pow(base, -1));
	for(int i = 1; i < n.tam; i++) {
		soma += (n.vet[i] * pow(base, (-i - 1)));
	}
	return soma;
}

double xToDecimal(BaseX s) {
	return ((double)xTointeiro(s.inteiro, s.base)) + xToDouble(s.fracionario, s.base);
}

BaseX leitura (int *is_decimal) {
	BaseX s;
	int base;
	printf("Insira a base do número: ");
	scanf("%d%*c", &base);
  printf("Qual número que deseja converter: ");
	if (base == 10) {
		*is_decimal = 1;
		scanf("%lf", &s.decimal);
		printf("Deseja transformar para qual base: ");
		scanf("%d", &s.base);

		s.fracionario.vet = alocaNum();
		s.inteiro.vet = alocaNum();
		decimalToX(&s);
		doubleToX(&s);
	}else {
		*is_decimal = 0;
		s.base = base;
		s.fracionario.vet = alocaNum();
		s.inteiro.vet = alocaNum();
		int acabou_num = lerNum(&s.inteiro, '.');
		if (!acabou_num) {
			lerNum(&s.fracionario, '\n');
		}

		printf("Deseja transformar para qual base: ");
		scanf("%d", &base);
		if (base == 10) {
			s.decimal = xToDecimal(s);
		}else {

		}
	}
	return s;
}

void liberaMem (BaseX s) {
	free(s.fracionario.vet);
	free(s.inteiro.vet);
}


