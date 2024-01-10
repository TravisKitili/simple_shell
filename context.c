#include "shell_interface.h"
/**
 *_myctxt - prints current environment
 *@data: structure
 *Return: 0 Always
 */
int _myctxt(insight_t *data)
{
	output_catalog_str(data->env);
	return (0);
}
/**
 *_getctxt - gets value of environ
 *@data: structure
 *@title: name
 *Return: value
 */
char *_getctxt(insight_t *data, const char *title)
{
	index_t *nexus = data->env;
	char *a;

	while (nexus)
	{
		a = embarks_with(nexus->str, title);
		if (a && *a)
			return (a);
		nexus = nexus->next;
	}
	return (NULL);
}
/**
 *_mysetctxt - initializes new environment
 *@data: structure
 *Return: 0 Always
 */
int _mysetctxt(insight_t *data)
{
	if (data->argc != 3)
	{
		_eprints("Incorrect number of arguements\n");
		return (1);
	}
	if (set_ambiance(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}
/**
 *_myunsetctxt - removes environment variable
 *@data: structure
 *Return: 0 Always
 */
int _myunsetctxt(insight_t *data)
{
	int a;

	if (data->argc == 1)
	{
		_eprints("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= data->argc; a++)
		unset_ambiance(data, data->argv[a]);
	return (0);
}
/**
 *inhabit_ctxt_list - populates linked list
 *@data: structure
 *Return: 0 Always
 */
int inhabit_ctxt_list(insight_t *data)
{
	index_t *nexus = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		append_nexus_end(&nexus, environ[a], 0);
	data->env = nexus;
	return (0);
}
