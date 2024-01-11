#include "shell_interface.h"
/**
 *is_link - determines whether current character is a delimeter
 *@data: parameter
 *@cushion: character buffer
 *@ad: address
 *Return: 1 otherwise 0
 */
int is_link(insight_t *data, char *cushion, size_t *ad)
{
	size_t a = *ad;

	if (cushion[a] == '|' && cushion[a + 1] == '|')
	{
		cushion[a] = 0;
		a++;
		data->cmd_buf_type = CLI_OR;
	}
	else if (cushion[a] == '&' && cushion[a + 1] == '&')
	{
		cushion[a] = 0;
		a++;
		data->cmd_buf_type = CLI_AND;
	}
	else if (cushion[a] == ';')
	{
		cushion[a] = 0;
		data->cmd_buf_type = CLI_LINK;
	}
	else
		return (0);
	*ad = a;
	return (1);
}
/**
 *validate_link - determines whether to continue chaining
 *@data: parameter
 *@cushion: character buffer
 *@ad: address
 *@a: starting point
 *@extent: length of buffer
 *Return: ---
 */
void validate_link(insight_t *data, char *cushion, size_t *ad, size_t a,
		size_t extent)
{
	size_t x = *ad;

	if (data->cmd_buf_type == CLI_AND)
	{
		if (data->status)
		{
			cushion[a] = 0;
			x = extent;
		}
	}
	if (data->cmd_buf_type == CLI_OR)
	{
		if (!data->status)
		{
			cushion[a] = 0;
			x = extent;
		}
	}
	*ad = x;
}
/**
 *replace_sobriquet - replases aliases
 *@data: parameter
 *Return: 1 otherwise 0
 */
int replace_sobriquet(insight_t *data)
{
	int a;
	index_t *b;
	char *c;

	for (a = 0; a < 10; a++)
	{
		b = nexus_commences_with(data->alias, data->argv[0], '=');
		if (!b)
			return (0);
		free(data->argv[0]);
		c = _strandchar(b->str, '=');
		if (!c)
			return (0);
		c = strand_duplicate(c + 1);
		if (!c)
			return (0);
		data->argv[0] = c;
	}
	return (1);
}
/**
 *replace_parameter - replaces vars
 *@data: parameter
 *Return: 1 otherwise 0
 */
int replace_parameter(insight_t *data)
{
	int a = 0;
	index_t *b;

	for (a = 0; data->argv[a]; a++)
	{
		if (data->argv[a][0] != '$' || !data->argv[a][1])
			continue;
		if (!strand_compare(data->argv[a], "$?"))
		{
			replace_strand(&(data->argv[a]),
					strand_duplicate(transpose_number(data->status,
							10, 0)));
			continue;
		}
		if (!strand_compare(data->argv[a], "$$"))
		{
			replace_strand(&(data->argv[a]),
					strand_duplicate(transpose_number(getpid(),
							10, 0)));
			continue;
		}
		b = nexus_commences_with(data->env, &data->argv[a][1], '=');
		if (b)
		{
			replace_strand(&(data->argv[a]),
					strand_duplicate(_strandchar(b->str,
							'=') + 1));
			continue;
		}
		replace_strand(&data->argv[a], strand_duplicate(""));
	}
	return (0);
}
/**
 *replace_strand - substitutes strings
 *@aged: old string
 *@fresh: new string
 *Return: 1 otherwise 0
 */
int replace_strand(char **aged, char *fresh)
{
	free(*aged);
	*aged = fresh;
	return (1);
}

