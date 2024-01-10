#include "shell_interface.h"
/**
 *my_record - displays history list
 *@data: structure
 *Return: 0 Always
 */
int my_record(insight_t *data)
{
	output_catalog(data->history);
	return (0);
}
/**
 *unset_sobriquet - sets alias
 *@data: parameter
 *@strng: string
 *Return: 0 Always
 */
int unset_sobriquet(insight_t *data, char *strng)
{
	char *a, b;
	int c;

	a = _strandchar(strng, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	c = eradicate_catalog_at_indicator(&(data->alias),
			acquire_nexus_indicator(data->alias,
				nexus_commences_with(data->alias, strng, -1)));
	*a = b;
	return (c);
}
/**
 *set_sobriquet - sets alias to strand
 *@data: parameter
 *@strng: string alias
 *Return: 0 Always
 */
int set_sobriquet(insight_t *data, char *strng)
{
	char *a;

	a = _strandchar(strng, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (unset_sobriquet(data, strng));
	unset_sobriquet(data, strng);
	return (append_nexus_end(&(data->alias), strng, 0) == NULL);
}
/**
 *print_sobriquet - prints alias string
 *@nexus: alias node
 *Return: 0 Always
 */
int print_sobriquet(index_t *nexus)
{
	char *a = NULL, *b = NULL;

	if (nexus)
	{
		a = _strandchar(nexus->str, '=');
		for (b = nexus->str; b <= a; b++)
			output_symbols(*b);
		output_symbols('\'');
		output_string(a + 1);
		output_string("'\n");
		return (0);
	}
	return (1);
}
/**
 *my_sobriquet - imitates the akias
 *@data: structure
 *Return: 0 Always
 */
int my_sobriquet(insight_t *data)
{
	int a = 0;
	char *b = NULL;
	index_t *nexus = NULL;

	if (data->argc == 1)
	{
		nexus = data->alias;
		while (nexus)
		{
			print_sobriquet(nexus);
			nexus = nexus->next;
		}
		return (0);
	}
	for (a = 1; data->argv[a]; a++)
	{
		b = _strandchar(data->argv[a], '=');
		if (b)
			set_sobriquet(data, data->argv[a]);
		else
			print_sobriquet(nexus_commences_with(data->alias,
						data->argv[a], '='));
	}
	return (0);
}
