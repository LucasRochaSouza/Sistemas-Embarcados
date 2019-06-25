/**
 * \file
 *
 * \brief Arquivo contendo o fluxo principal de controle do programa, utilizando as funcoes encontradas em outros arquivos.
 *
 */

#include <asf.h>

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "usart_driver.h"
#include "nvm_driver.h"
//! funcao contendo o controle de fluxo de programa, contendo a selecao do operadores e dos operandos
//! @param entrada string com o texto a ser processado
void ler_entrada(const char* entrada);

//! funcao implementando o metodo de newton-rhapson para solucao de equacoes
//! @param coef coeficientes do polinomio
//! @param n tamanho do polinomio
float poly_solver(const float* coef, int n);
//! funcao auxiliar para calcular o valor de um polinomio
//! @param coef coeficientes do polinomio
//! @param n tamanho do polinomio
//! @param x valor a ser calculado
float poly(const float* coef, int x, int n);
//! funcao auxiliar para calcular a derivada de um polinomio
//! @param coef coeficientes do polinomio
//! @param n tamanho do polinomio
float* poly_derivate(const float* coef, int n);

float variavel_carregada[3];
float resultado;
float a = 0;
float b = 0;

char entrada[80];
	
int main (void)
{

	char float_string[40];
	
	system_init();	
	init_usart();
	configure_nvm();		
	
	while(1) {
		scanf("%s", entrada);
		ler_entrada(entrada);
		ftoa(resultado, float_string, 4);
		printf("%s", float_string);
	}
}

void ler_entrada(const char* entrada) {
	int tamanho;

	char op_a[80];
	char op_b[80];

	tamanho = strlen(entrada);
	for (int i = 0; i < tamanho; i++) {
		if (entrada[i] == SOMA || entrada[i] == SUB || entrada[i] == MULT ||
		entrada[i] == DIV || entrada[i] == POW) {

			float a = 0;
			float b = 0;

			sub_string(entrada, op_a, 0, i);
			sub_string(entrada, op_b, i+1, tamanho - i - 1);

			a = atof2(op_a);
			b = atof2(op_b);

			if (strcmp(op_a, "x") == 0) {
				a = variavel_carregada[0];
			}
			else if (strcmp(op_a, "y") == 0) {
				a = variavel_carregada[1];
			}
			else if (strcmp(op_a, "z") == 0) {
				a = variavel_carregada[2];
			}

			if (strcmp(op_b, "x") == 0) {
				b = variavel_carregada[0];
			}
			else if (strcmp(op_b, "y") == 0) {
				b = variavel_carregada[1];
			}
			else if (strcmp(op_b, "z") == 0) {
				b = variavel_carregada[2];
			}
			if (entrada[i] == SOMA) {
				resultado = a + b;
			}
			else if (entrada[i] == SUB) {
				resultado = a - b;
			}
			else if (entrada[i] == MULT) {
				resultado = a * b;
			}
			else if (entrada[i] == DIV) {
				resultado = a / b;
			}
			else if (entrada[i] == POW) {
				resultado = pow(a, b);
			}
		}

		else if (entrada[i] == SEN || entrada[i] == COS || entrada[i] == TAN ||
		entrada[i] == LN || entrada[i] == SQRT || entrada[i] == LOG10) {
			sub_string(entrada, op_b, i + 1, tamanho - i - 1);		
						
			a = atof2(op_b);
			if (entrada[i] == SEN) {
				resultado = sinf(a);
			}
			else if (entrada[i] == COS) {
				resultado = cosf(a);
			}
			else if (entrada[i] == TAN) {
				resultado = tanf(a);
			}
			else if (entrada[i] == LN) {
				resultado = log(a);
			}
			else if (entrada[i] == SQRT) {
				resultado = sqrtf(a);
			}
			else if (entrada[i] == LOG10) {
				resultado = log10f(a);
			}
			printf("%f", resultado);
		}

		else if (entrada[i] == STORE) {
			sub_string(entrada, op_a, 0, i);
			sub_string(entrada, op_b, i + 1, tamanho - i - 1);

			float a = atof2(op_a);

			if (strcmp(op_b, "x") == 0) {
				variavel_carregada[0] = a;
			}
			else if (strcmp(op_b, "y") == 0) {
				variavel_carregada[1] = a;
			}
			else if (strcmp(op_b, "z") == 0) {
				variavel_carregada[2] = a;
			}
		}
		
		else if (entrada[i] == POLY) {
			
		}
		
		else if(entrada[i] == FLASH_STORE) {
			sub_string(entrada, op_a, 0, i);
			sub_string(entrada, op_b, i + 1, tamanho - i - 1);
			
			float a = atof2(op_a);
			int address = atoi(op_b);
			
			if (strcmp(op_b, "x") == 0) {
				variavel_carregada[0] = a;
			}
			else if (strcmp(op_b, "y") == 0) {
				variavel_carregada[1] = a;
			}
			else if (strcmp(op_b, "z") == 0) {
				variavel_carregada[2] = a;
			}	
			write_float(address, a);						
		}
			
		else if(entrada[i] == FLASH_LOAD) {
			sub_string(entrada, op_a, 0, i);
			sub_string(entrada, op_b, i + 1, tamanho - i - 1);
			
			int address = atoi(op_b);
			
			float a = read_float(address);
			
			if (strcmp(op_a, "x") == 0) {
				variavel_carregada[0] = a;
			}
			else if (strcmp(op_a, "y") == 0) {
				variavel_carregada[1] = a;
			}
			else if (strcmp(op_a, "z") == 0) {
				variavel_carregada[2] = a;
			} else {
				variavel_carregada[0] = a;
			}
		}
	}
}

float poly(const float* coef, int x, int n) {
	float sum = 0;
	int j = n - 1;
	for (int i = 0; i < n; i++) {
		sum += coef[j]*pow(x, i);
		j--;
	}
	return sum;
}

float* poly_derivate(const float* coef, int n) {
	int j = n - 1;
	float* coef_derivate = (float*)malloc((n - 1) * sizeof(float));

	for (int i = 0; i < n-1; i++) {
		coef_derivate[i] = coef[i] * j;
		j--;
	}

	return coef_derivate;
}

float poly_solver(const float* coef, int n) {
	int itr;
	float h, x1;

	int maxmitr = 40;
	float error = 0.05;

	float* derivate_coef = poly_derivate(coef, n);

	float x0 = 0;
	
	for (itr = 1; itr <= maxmitr; itr++)
	{
		h = poly(coef, x0, n) / poly(derivate_coef, x0, n - 1);

		x1 = x0 - h;

		if (fabs(h) < error)
		{
			return x1;
		}
		x0 = x1;
	}
	return x1;
}









