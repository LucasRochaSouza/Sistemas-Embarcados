/** arquivo contendo algumas funções auxiliares de manipulação de string. 
/**
 * \file
 * \brief
 * \Arquivo utilitario para manipulação de string e float
 *
 */


#ifndef UTILS_H_
#define UTILS_H_

#include <string.h>
#include <tgmath.h>
#include <arm_math.h>
#include <ctype.h>

#define SOMA			'+'
#define SUB				'-'
#define MULT			'*'
#define DIV				'/'
#define POW				'^'
#define COS				'c'
#define SEN				's'
#define TAN				't'
#define SQRT			'q'
#define LN				'l'
#define LOG10			'd'

#define STORE			'r'
#define FLASH_STORE		'>'
#define FLASH_LOAD		'<'

#define POLY			'p'


//! Funcao para converter um conjunto de 4 bytes em um valor com ponto flutuante
//! @param str Ponteiro apontando para o vetor de 4 bytes
float atof2(const char *str);
//! Funcao para converter um valor float para uma string
//! @param n valor float a ser convertido
//! @param res ponteiro onde vai ser armazenada a string
//! @param afterpoint numero de casas apos a virgula
void ftoa(float n, char *res, int afterpoint);
//! Funcao auxiliar para implementacao de ftoa
void reverse(char *str, int len);
//! Funcao auxiliar para implementacao de ftoa
int intToStr(int x, char str[], int);
//! Funcao auxiliar para dividir uma string em outra menor
//! @param src ponteiro com a string original
//! @param dest ponteiro com a string a ser copiada
//! @param offset da memoria
//! @param len tamanho da string copiada
char* sub_string(const char* src, char* dest, int offset, int len);

#endif /* UTILS_H_ */