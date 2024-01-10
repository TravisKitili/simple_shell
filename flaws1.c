#include "shell_interface.h"
/**
 *_errstrtol - convertsstring to number
 *@strn: string
 *Return: 0 otherwise -1
 */
int _errstrtol(char *strn)
{
	int a = 0;
	unsigned long int b = 0;

	if (*strn == '+')
		strn++;
	for (a = 0; strn[a] != '\0'; a++)
	{
		if (strn[a] >= '0' && strn[a] <= '9')
		{
			b *= 10;
			b += (strn[a] - '0');
			if (b > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (b);
}
/**
 *print_flaw - prints error message
 *@data: parameter
 *@strng: string
 *Return: 0 otherwise -1
 */
void print_flaw(insight_t *data, char *strng)
{
	_eprints(data->fname);
	_eprints(": ");
	output_d(data->line_count, STDERR_FILENO);
	_eprints(": ");
	_eprints(data->argv[0]);
	_eprints(": ");
	_eprints(strng);
}
/**
 *output_d - prints decimal number
 *@entry: input
 *@filedesc: file descriptor
 *Return: no. of characters
 */
int output_d(int entry, int filedesc)
{
	int (*writechar)(char) = output_symbols;
	int a, b = 0;
	unsigned int c, d;

	if (filedesc == STDERR_FILENO)
		writechar = _eputc;
	if (entry < 0)
	{
		c = -entry;
		writechar('-');
		b++;
	}
	else
		c = entry;
	d = c;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (c / a)
		{
			writechar('0' + d / a);
		}
		d %= a;
	}
	writechar('0' + d);
	b++;
	return (b);
}
/**
 *transpose_number - converts function
 *@intg: integer
 *@substrate: the base
 *@parameter: arguments
 *Return: the string
 */
char *transpose_number(long int intg, int substrate, int parameter)
{
	static char *a;
	static char temp[50];
	char b = 0;
	char *c;
	unsigned long d = intg;

	if (!(parameter & TRANSPOSE_NON_NEGATIVE) && intg < 0)
	{
		d = -intg;
		b = '-';
	}
	a = parameter & TRANSPOSE_MINISCULE ? "0123456789abcdef" :
		"0123456789ABCDEF";
	c = &temp[49];
	*c = '\0';
	do {
		*--c = a[d % substrate];
		d /= substrate;
	} while (d != 0);
	if (b)
		*--c = b;
	return (c);
}
/**
 *oust_comments - replaces # with '\0'
 *@temp: address
 *Return: 0 Always
 */
void oust_comments(char *temp)
{
	int a;

	for (a = 0; temp[a] != '\0'; a++)
		if (temp[a] == '#' && (!a || temp[a - 1] == ' '))
		{
			temp[a] = '\0';
			break;
		}
}

