#include "shell_interface.h"
/**
 *_eprints - prints input string
 *@strng: string
 *Return: ---
 */
void _eprints(char *strng)
{
	int a = 0;

	if (!strng)
		return;
	while (strng[a] != '\0')
	{
		_eputc(strng[a]);
		a++;
	}
}
/**
 *_eputc - writes character to standard err
 *@x: charcter
 *Return: 1 on success otherwise -1
 */
int _eputc(char x)
{
	static int a;
	static char b[CRAFT_BUF_EXTENT];

	if (x == BUF_PURGE || a >= CRAFT_BUF_EXTENT)
	{
		write(2, b, a);
		a = 0;
	}
	if (x != BUF_PURGE)
		b[a++] = x;
	return (1);
}
/**
 *_depictfd - writes character to given file descriptor
 *@x: character
 *@filedesc: fd to write
 *Return: 1 on success otherwise -1
 */
int _depictfd(char x, int filedesc)
{
	static int a;
	static char b[CRAFT_BUF_EXTENT];

	if (x == BUF_PURGE || a >= CRAFT_BUF_EXTENT)
	{
		write(filedesc, b, a);
		a = 0;
	}
	if (x != BUF_PURGE)
		b[a++] = x;
	return (1);
}
/**
 *_depictsfd - prints input string
 *@strng: string
 *@filedesc: fie descriptor
 *Return: number of characters
 */
int _depictsfd(char *strng, int filedesc)
{
	int a = 0;

	if (!strng)
		return (0);
	while (*strng)
	{
		a += _depictfd(*strng++, filedesc);
	}
	return (a);
}
