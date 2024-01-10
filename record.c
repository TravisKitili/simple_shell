#include "shell_interface.h"
/**
 *get_recordfile - gets record file
 *@data: parameter
 *Return: allocated string
 */
char *get_recordfile(insight_t *data)
{
	char *a, *b;

	b = _getctxt(data, "HOME=");
	if (!b)
		return (NULL);
	a = malloc(sizeof(char) * (strand_length(b)
				+ strand_length(HIST_RECORD) + 2));
	if (!a)
		return (NULL);
	a[0] = 0;
	strand_copy(a, b);
	strand_concat(a, "/");
	strand_concat(a, HIST_RECORD);
	return (a);
}
/**
 *write_record - creates a file
 *@data: parameter
 *Return: 1 otherwise -1
 */
int write_record(insight_t *data)
{
	ssize_t filedesc;
	char *a = get_recordfile(data);
	index_t *b = NULL;

	if (!a)
		return (-1);
	filedesc = open(a, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(a);
	if (filedesc == -1)
		return (-1);
	for (b = data->history; b; b = b->next)
	{
		_depictsfd(b->str, filedesc);
		_depictfd('\n', filedesc);
	}
	_depictfd(BUF_PURGE, filedesc);
	close(filedesc);
	return (1);
}
/**
 *decipher_record - reads records from a file
 *@data: parameter
 *Return: histcount
 */
int decipher_record(insight_t *data)
{
	int a, b = 0, c = 0;
	ssize_t filedesc, d, e = 0;
	struct stat f;
	char *g = NULL, *h = get_recordfile(data);

	if (!h)
		return (0);
	filedesc = open(h, O_RDONLY);
	free(h);
	if (filedesc == -1)
		return (0);
	if (!fstat(filedesc, &f))
		e = f.st_size;
	if (e < 2)
		return (0);
	g = malloc(sizeof(char) * (e + 1));
	if (!g)
		return (0);
	d = read(filedesc, g, e);
	g[e] = 0;
	if (d <= 0)
		return (free(g), 0);
	close(filedesc);
	for (a = 0; a < e; a++)
		if (g[a] == '\n')
		{
			g[a] = 0;
			fabricate_recordlist(data, g + b, c++);
			c = a + 1;
		}
	if (b != a)
		fabricate_recordlist(data, g + b, c++);
	free(g);
	data->histcount = c;
	while (data->histcount-- >= HIST_PEAK)
		eradicate_catalog_at_indicator(&(data->history), 0);
	reorder_record(data);
	return (data->histcount);
}
/**
 *fabricate_recordlist - adds entry to list
 *@data: structure
 *@storage: buffer
 *@linetally: history linecount
 *Return: 0 Always
 */
int fabricate_recordlist(insight_t *data, char *storage, int linetally)
{
	index_t *a = NULL;

	if (data->history)
		a = data->history;
	append_nexus_end(&a, storage, linetally);
	if (!data->history)
		data->history = a;
	return (0);
}
/**
 *reorder_record - renumbers record list
 *@data: structure
 *Return: new histtally
 */
int reorder_record(insight_t *data)
{
	index_t *nexus = data->history;
	int x = 0;

	while (nexus)
	{
		nexus->num = x++;
		nexus = nexus->next;
	}
	return (data->histcount = x);
}
