#include "shell_interface.h"
/**
 *get_context - returns string array
 *@data: structure
 *Return: 0 Always
 */
char **get_context(insight_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = catalog_to_strands(data->env);
		data->env_changed = 0;
	}
	return (data->environ);
}
/**
 *unset_ambiance - remove envt variable
 *@data: structure
 *@param: string property
 *Return: 1 otherwise 0
 */
int unset_ambiance(insight_t *data, char *param)
{
	index_t *nexus = data->env;
	size_t a = 0;
	char *b;

	if (!nexus || !param)
		return (0);
	while (nexus)
	{
		b = embarks_with(nexus->str, param);
		if (b && *b == '=')
		{
			data->env_changed = eradicate_catalog_at_indicator(&
					(data->env), a);
			a = 0;
			nexus = data->env;
			continue;
		}
		nexus = nexus->next;
		a++;
	}
	return (data->env_changed);
}
/**
 *set_ambiance - initializes new variable
 *@data: structure
 *@param: parameter
 *@worth: string value
 *Return: 0 Always
 */
int set_ambiance(insight_t *data, char *param, char *worth)
{
	char *temp = NULL;
	index_t *nexus;
	char *a;

	if (!param || worth)
		return (0);
	temp = malloc(strand_length(param) + strand_length(worth) + 2);
	if (!temp)
		return (1);
	strand_copy(temp, param);
	strand_concat(temp, "=");
	strand_concat(temp, worth);
	nexus = data->env;
	while (nexus)
	{
		a = embarks_with(nexus->str, param);
		if (a && *a == '=')
		{
			free(nexus->str);
			nexus->str = temp;
			data->env_changed = 1;
			return (0);
		}
		nexus = nexus->next;
	}
	append_nexus_end(&(data->env), temp, 0);
	free(temp);
	data->env_changed = 1;
	return (0);
}
