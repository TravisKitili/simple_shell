#include "shell_interface.h"
/**
 *responsive - returns true if interactive
 *@data: structure address
 *Return: 1 otherwise 0
 */
int responsive(insight_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}
/**
 *is_divider - checks for delimeters
 *@a: character
 *@divid: delimeter string
 *Return: 1 otherwise 0
 */
int is_divider(char a, char *divid)
{
	while (*divid)
		if (*divid++ == a)
			return (1);
	return (0);
}
/**
 *is_letterset - checks for characters
 *@x: character
 *Return: 1 otherwise 0
 */
int is_letterset(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 *parsefloat - converts string to number
 *@strn: string
 *Return: converted number otherwise 0
 */
int parsefloat(char *strn)
{
	int a, b = 1, c = 0, result;
	unsigned int yield = 0;

	for (a = 0; strn[a] != '\0' && c != 2; a++)
	{
		if (strn[a] == '-')
			b *= -1;
		if (strn[a] >= '0' && strn[a] <= '9')
		{
			c = 1;
			yield *= 10;
			yield += (strn[a] - '0');
		}
		else if (c == 1)
			c = 2;
	}
	if (b == -1)
		result = -yield;
	else
		result = yield;
	return (result);
}
