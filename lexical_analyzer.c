#include "shell_interface.h"
/**
 *segmentwords - splits string to words
 *@strn: string
 *@sep: delimeter
 *Return: pointer
 */
char **segmentwords(char *strn, char *sep)
{
	int a, b, c, d, e = 0;
	char **f;

	if (strn == NULL || strn[0] == 0)
		return (NULL);
	if (!sep)
		sep = " ";
	for (a = 0; strn[a] != '\0'; a++)
		if (!is_divider(strn[a], sep) && (is_divider(strn[a + 1], sep)
					|| !strn[a + 1]))
			e++;
	if (e == 0)
		return (NULL);
	f = malloc((1 + e) * sizeof(char *));
	if (!f)
		return (NULL);
	for (a = 0, b = 0; b < e; b++)
	{
		while (is_divider(strn[a], sep))
			a++;
		c = 0;
		while (!is_divider(strn[a + c], sep) && strn[a + c])
			c++;
		f[b] = malloc((c + 1) * sizeof(char));
		if (!f[b])
		{
			for (c = 0; c < b; c++)
				free(f[c]);
			free(f);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			f[b][d] = strn[a++];
		f[b][d] = 0;
	}
	f[b] = NULL;
	return (f);
}
/**
 *segmentwords2 - split string to words
 *@strn: input string
 *@sep: delimeter
 *Return: pointer
 */
char **segmentwords2(char *strn, char sep)
{
	int a, b, c, d, e = 0;
	char **f;

	if (strn == NULL || strn[0] == 0)
		return (NULL);
	for (a = 0; strn[a] != '\0'; a++)
		if ((strn[a] != sep && strn[a + 1] == sep) ||
				(strn[a] != sep && !strn[a + 1]) ||
				strn[a + 1] == sep)
			e++;
	if (e == 0)
		return (NULL);
	f = malloc((1 + e) * sizeof(char *));
	if (!f)
		return (NULL);
	for (a = 0, b = 0; b < e; b++)
	{
		while (strn[a] == sep && strn[a] != sep)
			a++;
		c = 0;
		while (strn[a + c] != sep && strn[a + c] && strn[a + c] != sep)
			c++;
		f[b] = malloc((c + 1) * sizeof(char));
		if (!f[b])
		{
			for (c = 0; c < b; c++)
				free(f[c]);
			free(f);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			f[b][d] = strn[a++];
		f[b][d] = 0;
	}
	f[b] = NULL;
	return (f);
}
