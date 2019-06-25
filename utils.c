
#include "utils.h"


char* sub_string(const char* src, char* dest, int offset, int len)
{
	int input_len = strlen(src);

	if (offset + len > input_len)
	{
		return NULL;
	}

	strncpy(dest, src + offset, len);
	dest[len] = '\0';
	return dest;
}

// Código sem a minha autoria
// Créditos: Edward Karak
// Link: https://codereview.stackexchange.com/questions/119986/atof-implementation

float atof2(const char *str)
{
	float a;           /* the a value in a*10^b */
	float decplace;    /* number to divide by if decimal point is seen */
	float b;           /* The b value (exponent) in a*10^b */

	int sign = 1;       /* stores the sign of a */
	int bsign = 1;      /* stores the sign of b */

	while (*str && isspace(*str))
	++str;

	if (*str == '+')
	++str;
	if (*str == '-') {
		sign = -1;
		++str;
	}
	if ((*str == 'n' || *str == 'N') &&
	(str[1] == 'a' || str[1] == 'A')
	&& (str[2] == 'n' || str[2] == 'N'))
	return NAN * sign;
	if ((*str == 'i' || *str == 'I') && (str[1] == 'n' || str[1] == 'N') &&
	(str[2] == 'f' || str[2] == 'F'))
	return INFINITY * sign;

	for (a = 0; *str && isdigit(*str); ++str)
	a = a * 10 + (*str - '0');

	if (*str == '.')
	++str;
	for (decplace = 1.; *str && isdigit(*str); ++str, decplace *= 10.)
	a = a * 10. + (*str - '0');

	if (*str == 'e' || *str == 'E') {
		/* if the user types a string starting from e, make the base be 1 */
		if (a == 0)
		a = 1;
		++str;
		if (*str == '-') {
			bsign = -1;
			++str;
		}
		if (*str == '+')
		++str;
		for (b = 0; *str && isdigit(*str); ++str)
		b = b * 10 + (*str - '0');

		b *= bsign;
	}
	else
	b = 0;

	return (a * sign / decplace) * pow(10, b);
}

// Código sem a minha autoria
// Créditos: Autor Desconhecido
// Link: https://codereview.stackexchange.com/questions/119986/atof-implementation

void reverse(char *str, int len)
{
	int i=0, j=len-1, temp;
	while (i<j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++; j--;
	}
}

int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x)
	{
		str[i++] = (x%10) + '0';
		x = x/10;
	}
	
	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
	str[i++] = '0';
	
	reverse(str, i);
	str[i] = '\0';
	return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
	// Extract integer part
	int ipart = (int)n;
	
	// Extract floating part
	float fpart = n - (float)ipart;
	
	// convert integer part to string
	int i = intToStr(ipart, res, 0);
	
	// check for display option after point
	if (afterpoint != 0)
	{
		res[i] = '.';  // add dot
		
		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter is needed
		// to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint) + 0.5;
		
		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}