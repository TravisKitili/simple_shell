#include "shell_interface.h"
/**
 *_strandclone - replicates a string
 *@endpoint: destination
 *@origin: source
 *@a: amount of characters
 *Return: replicated string
 */
char *_strandclone(char *endpoint, char *origin, int a)
{
	int r, s;
	char *t = endpoint;

	r = 0;
	while (origin[r] != '\0' && r < a - 1)
	{
		endpoint[r] = origin[r];
		r++;
	}
	if (r < a)
	{
		s = r;
		while (s < a)
		{
			endpoint[s] = '\0';
			s++;
		}
	}
	return (t);
}
/**
 *_strandcat - merges two strings
 *@endpoint: first string
 *@origin: second string
 *@a: amount of bytes
 *Return: merged string
 */
char *_strandcat(char *endpoint, char *origin, int a)
{
	int x, y;
	char *z = endpoint;

	x = 0;
	y = 0;
	while (endpoint[x] != '\0')
		x++;
	while (origin[y] != '\0' && y < a)
	{
		endpoint[x] = origin[y];
		x++;
		y++;
	}
	if (y < a)
		endpoint[x] = '\0';
	return (z);
}
/**
 *_strandchar - locates characters
 *@strn: string
 *@chr: character
 *Return: pointer
 */
char *_strandchar(char *strn, char chr)
{
	do {
		if (*strn == chr)
			return (strn);
	} while (*strn++ != '\0');
	return (NULL);
}
