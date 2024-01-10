#include "shell_interface.h"
/**
 *_populate - fills memory
 *@a: pointer to memory area
 *@b: byte
 *@c: amount of bytes
 *Return: pointer to memory area
 */
char *_populate(char *a, char b, unsigned int c)
{
	unsigned int x;

	for (x = 0; x < c; x++)
		a[x] = b;
	return (a);
}
/**
 *liberate_string - frees a string
 *@strn: strings
 */
void liberate_string(char **strn)
{
	char **i = strn;

	if (!strn)
		return;
	while (*strn)
		free(*strn++);
	free(i);
}
/**
 *_reshape - reallocates memory
 *@pnt: pointer
 *@olsze: size
 *@nwsze: byte size
 *Return: pointer
 */
void *_reshape(void *pnt, unsigned int olsze, unsigned int nwsze)
{
	char *a;

	if (!pnt)
		return (malloc(nwsze));
	if (!nwsze)
		return (free(pnt), NULL);
	if (nwsze == olsze)
		return (pnt);
	a = malloc(nwsze);
	if (!a)
		return (NULL);
	olsze = olsze < nwsze ? olsze : nwsze;
	while (olsze--)
		a[olsze] = ((char *)pnt)[olsze];
	free(pnt);
	return (a);
}
