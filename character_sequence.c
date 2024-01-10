#include "shell_interface.h"
/**
 *strand_length - returns length of string
 *@strng: string
 *Return: number length
 */
int strand_length(char *strng)
{
	int a = 0;

	if (!strng)
		return (0);
	while (*strng++)
		a++;
	return (a);
}
/**
 *strand_compare - performs comparisons
 *@str1: first string
 *@str2: second string
 *Return: value
 */
int strand_compare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
/**
 *embarks_with - determins whether pin starts with heap
 *@heap: string
 *@pin: substring
 *Return: address of next character
 */
char *embarks_with(const char *heap, const char *pin)
{
	while (*pin)
		if (*pin++ != *heap++)
			return (NULL);
	return ((char *)heap);
}
/**
 *strand_concat - meges two strings
 *@endpoint: destination buffer
 *@origin: source buffer
 *Return: pointer
 */
char *strand_concat(char *endpoint, char *origin)
{
	char *a = endpoint;

	while (*endpoint)
		endpoint++;
	while (*origin)
		*endpoint++ = *origin++;
	*endpoint = origin;
	return (a);
}

