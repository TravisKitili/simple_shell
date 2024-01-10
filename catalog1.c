#include "shell_interface.h"
/**
 *catalog_extent - determines length of list
 *@a: pointer
 *Return: size
 */
size_t catalog_extent(const index_t *a)
{
	size_t x = 0;

	while (a)
	{
		a = a->next;
		x++;
	}
	return (x);
}
/**
 *catalog_to_strands - returns array
 *@chief: pointer
 *Return: array
 */
char **catalog_to_strands(index_t *chief)
{
	index_t *a = chief;
	size_t b = catalog_extent(chief), c;
	char **d;
	char *e;

	if (!chief || !b)
		return (NULL);
	d = malloc(sizeof(char *) * (b + 1));
	if (!d)
		return (NULL);
	for (b = 0; a; a = a->next, b++)
	{
		e = malloc(strand_length(a->str) + 1);
		if (!e)
		{
			for (c = 0; c < b; c++)
				free(d[c]);
			free(d);
			return (NULL);
		}
		e = strand_copy(e, a->str);
		d[b] = e;
	}
	d[b] = NULL;
	return (d);
}
/**
 *output_catalog - prints elements of linked list
 *@a: pointer
 *Return: list size
 */
size_t output_catalog(const index_t *a)
{
	size_t b = 0;

	while (a)
	{
		output_string(transpose_number(a->num, 10, 0));
		output_symbols(':');
		output_symbols(' ');
		output_string(a->str ? a->str : "(nil)");
		output_string("\n");
		a = a->next;
		b++;
	}
	return (b);
}
/**
 *nexus_commences_with - returns node
 *@nexus: pointer
 *@prelude: string
 *@a: character after prelude
 *Return: nexus or null
 */
index_t *nexus_commences_with(index_t *nexus, char *prelude, char a)
{
	char *b = NULL;

	while (nexus)
	{
		b = embarks_with(nexus->str, prelude);
		if (b && ((a == -1) || (*b == a)))
			return (nexus);
		nexus = nexus->next;
	}
	return (NULL);
}
/**
 *acquire_nexus_indicator - acquires node index
 *@chief: pointer
 *@nexus: pointer
 *Return: node index otherwise -1
 */
ssize_t acquire_nexus_indicator(index_t *chief, index_t *nexus)
{
	size_t a = 0;

	while (chief)
	{
		if (chief == nexus)
			return (a);
		chief = chief->next;
		a++;
	}
	return (-1);
}
