#include "shell_interface.h"
/**
 *clear_insight - initializes passdata structure
 *@data: structure
 */
void clear_insight(insight_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}
/**
 *set_insight - intiatializes structure
 *@data: structure
 *@argvt: argument vector
 */
void set_insight(insight_t *data, char **argvt)
{
	int a = 0;

	data->fname = argvt[0];
	if (data->arg)
	{
		data->argv = segmentwords(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = strand_duplicate(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (a = 0; data->argv && data->argv[a]; a++)
			;
		data->argc = a;
		replace_sobriquet(data);
		replace_parameter(data);
	}
}
/**
 *free_insight - frees passdata structure fields
 *@data: structure
 *@entire: true
 */
void free_insight(insight_t *data, int entire)
{
	liberate_string(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (entire)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			free_catalog(&(data->env));
		if (data->history)
			free_catalog(&(data->history));
		if (data->alias)
			free_catalog(&(data->alias));
		liberate_string(data->environ);
		data->environ = NULL;
		bcrisp((void **)data->cmd_buf);
		if (data->readfd > 2)
			close(data->readfd);
		output_symbols(BUF_PURGE);
	}
}
