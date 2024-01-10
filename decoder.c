#include "shell_interface.h"
/**
 *is_prompt - checks if a file is a command
 *@data: insight struct
 *@route: file path
 *Return: 1 if true otherwise 0
 */
int is_prompt(insight_t *data, char *route)
{
	struct stat ax;

	(void)data;
	if (!route || stat(route, &ax))
		return (0);

	if (ax.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 *dup_glyphs - replicates characters
 *@routestr: route string
 *@commence: starting indicator
 *@cease: stopping indicator
 *Return: pointer
 */
char *dup_glyphs(char *routestr, int commence, int cease)
{
	static char tempstorage[1024];
	int a = 0, b = 0;

	for (b = 0, a = commence; a < cease; a++)
		if (routestr[a] != ':')
			tempstorage[b++] = routestr[a];
	tempstorage[b] = 0;
	return (tempstorage);
}
/**
 *find_route - finds command in path
 *@data: passdata struct
 *@routestr: route string
 *@prompt: command
 *Return: full command path
 */
char *find_route(insight_t *data, char *routestr, char *prompt)
{
	int a = 0, b = 0;
	char *c;

	if (!routestr)
		return (NULL);
	if ((strand_length(prompt) > 2) && embarks_with(prompt, "./"))
	{
		if (is_prompt(data, prompt))
			return (prompt);
	}
	while (1)
	{
		if (!routestr[a] || routestr[a] == ':')
		{
			c = dup_glyphs(routestr, b, a);
			if (!*c)
				strand_concat(c, prompt);
			else
			{
				strand_concat(c, "/");
				strand_concat(c, prompt);
			}
			if (is_prompt(data, c))
				return (c);
			if (!routestr[a])
				break;
			b = a;
		}
		a++;
	}
	return (NULL);
}
