#include "shell_interface.h"
/**
 *strand_copy - copies a string
 *@endpoint: destination
 *@origin: source
 *Return: pointer
 */
char *strand_copy(char *endpoint, char *origin)
{
	int a = 0;

	if (endpoint == origin || origin == 0)
		return (endpoint);
	while (origin[a])
	{
		endpoint[a] = origin[a];
		a++;
	}
	endpoint[a] = 0;
	return (endpoint);
}
/**
 *strand_duplicate - replicates a string
 *@strng: string
 *Return: pointer
 */
char *strand_duplicate(const char *strng)
{
	int a = 0;
	char *b;

	if (strng == NULL)
		return (NULL);
	while (*strng++)
		a++;
	b = malloc(sizeof(char) * (a + 1));
	if (!b)
		return (NULL);
	for (a++; a--;)
		b[a] = *--strng;
	return (b);
}
/**
 *output_string - prints input string
 *@strng: string
 *Return: ---
 */
void output_string(char *strng)
{
	int a = 0;

	if (!strng)
		return;
	while (strng[a] != '\0')
	{
		output_symbols(strng[a]);
		a++;
	}
}
/**
 *output_symbols - writes characters to the standard output
 *@x: character
 *Return: 1 on success otherwise -1
 */
int output_symbols(char x)
{
	static int a;
	static char b[CRAFT_BUF_EXTENT];

	if (x == BUF_PURGE || a >= CRAFT_BUF_EXTENT)
	{
		write(1, b, a);
		a = 0;
	}
	if (x != BUF_PURGE)
		b[a++] = x;
	return (1);
}
