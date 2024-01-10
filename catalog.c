#include "shell_interface.h"
/**
 *append_nexus - adds a node
 *@chief: pointer address
 *@strn: str field
 *@intg: node index
 *Return: size
 */
index_t *append_nexus(index_t **chief, const char *strn, int intg)
{
	index_t *a;

	if (!chief)
		return (NULL);
	a = malloc(sizeof(index_t));
	if (!a)
		return (NULL);
	_populate((void *)a, 0, sizeof(index_t));
	a->num = intg;
	if (strn)
	{
		a->str = strand_duplicate(strn);
		if (!a->str)
		{
			free(a);
			return (NULL);
		}
	}
	a->next = *chief;
	*chief = a;
	return (a);
}
/**
 *append_nexus_end - adds node to the end
 *@chief: pointer address
 *@strn: str field
 *@intg: node index
 *Return: size
 */
index_t *append_nexus_end(index_t **chief, const char *strn, int intg)
{
	index_t *a, *nexus;

	if (!chief)
		return (NULL);
	nexus = *chief;
	a = malloc(sizeof(index_t));
	if (!a)
		return (NULL);
	_populate((void *)a, 0, sizeof(index_t));
	a->num = intg;
	if (strn)
	{
		a->str = strand_duplicate(strn);
		if (!a->str)
		{
			free(a);
			return (NULL);
		}
	}
	if (nexus)
	{
		while (nexus->next)
			nexus = nexus->next;
		nexus->next = a;
	}
	else
		*chief = a;
	return (a);
}
/**
 *output_catalog_str - prints str elements
 *@a: pointer
 *Return: size
 */
size_t output_catalog_str(const index_t *a)
{
	size_t b = 0;

	while (a)
	{
		output_string(a->str ? a->str : "(nil)");
		output_string("\n");
		a = a->next;
		b++;
	}
	return (b);
}
/**
 *eradicate_catalog_at_indicator - deletes node at indicator
 *@chief: pointer address
 *@indicator: index of node
 *Return: 1 otherwise 0
 */
int eradicate_catalog_at_indicator(index_t **chief, unsigned int indicator)
{
	index_t *a, *b;
	unsigned int c = 0;

	if (!chief || !*chief)
		return (0);
	if (!indicator)
	{
		a = *chief;
		*chief = (*chief)->next;
		free(a->str);
		free(a);
		return (1);
	}
	a = *chief;
	while (a)
	{
		if (c == indicator)
		{
			b->next = a->next;
			free(a->str);
			free(a);
			return (1);
		}
		c++;
		b = a;
		a = a->next;
	}
	return (0);
}
/**
 *free_catalog - frees all nodes
 *@chief: pointer address
 *Return: ---
 */
void free_catalog(index_t **chief)
{
	index_t *nexus, *next_nexus, *captain;

	if (!chief || !*chief)
		return;
	captain = *chief;
	nexus = captain;
	while (nexus)
	{
		next_nexus = nexus->next;
		free(nexus->str);
		free(nexus);
		nexus = next_nexus;
	}
	*chief = NULL;
}

