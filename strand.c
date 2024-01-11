#include "shell_interface.h"
/**
 *input_temp - buffers chained commands
 *@data: parameter
 *@temp: buffer address
 *@extent: address
 *Return: bytes
 */
ssize_t input_temp(insight_t *data, char **temp, size_t *extent)
{
	ssize_t a = 0;
	size_t b = 0;

	if (!*extent)
	{
		/* bcrisp((void **)data->cmd_buf); */
		free(*temp);
		*temp = NULL;
		signal(SIGINT, interrupt_handler);
#if HARNESS_FGETS
		a = getline(temp, &b, stdin);
#else
		a = _getstrand(data, temp, &b);
#endif
		if (a > 0)
		{
			if ((*temp)[a - 1] == '\n')
			{
				(*temp)[a - 1] = '\0';
				a--;
			}
			data->linecount_flag = 1;
			oust_comments(*temp);
			fabricate_recordlist(data, *temp, data->histcount++);
			/* if(_strandchar(*temp, ';')) is prompt link? */
			{
				*extent = a;
				data->cmd_buf = temp;
			}
		}
	}
	return (a);
}
/**
 *get_dataentry - gets aline
 *@data: parameter
 *Return: bytes
 */
ssize_t get_dataentry(insight_t *data)
{
	static char *temp;
	static size_t a, b, c;
	ssize_t d = 0;
	char **e = &(data->arg), *f;

	output_symbols(BUF_PURGE);
	d = input_temp(data, &temp, &c);
	if (d == -1)
		return (-1);
	if (c)
	{
		b = a;
		f = temp + a;
		validate_link(data, temp, &b, a, c);
		while (b < c)
		{
			if (is_link(data, temp, &b))
				break;
			b++;
		}
		a = b + 1;
		if (a >= c)
		{
			a = c = 0;
			data->cmd_buf_type = CLI_CUSTOM;
		}
		*e = f;
		return (strand_length(f));
	}
	*e = temp;
	return (d);
}
/**
 *peruse_temp - goes over a buffer
 *@data: parameter
 *@temp: buffer
 *@a: extent
 *Return: b
 */
ssize_t peruse_temp(insight_t *data, char *temp, size_t *a)
{
	ssize_t b = 0;

	if (*a)
		return (0);
	b = read(data->readfd, temp, DECIPHER_BUF_EXTENT);
	if (b >= 0)
		*a = b;
	return (b);
}
/**
 *_getstrand - gets the next line
 *@data: parameter
 *@ab: pointer address
 *@extent: size
 *Return: e
 */
int _getstrand(insight_t *data, char **ab, size_t *extent)
{
	static char temp[DECIPHER_BUF_EXTENT];
	static size_t a, b;
	size_t c;
	ssize_t d = 0, e = 0;
	char *f = NULL, *g = NULL, *h;

	f = *ab;
	if (f && extent)
		e = *extent;
	if (a == b)
		a = b = 0;
	d = peruse_temp(data, temp, &b);
	if (d == -1 || (d == 0 && b == 0))
		return (-1);
	h = _strandchar(temp + a, '\n');
	c = h ? 1 + (unsigned int)(h - temp) : b;
	g = _reshape(f, e, e ? e + c : c + 1);
	if (!g)
		return (f ? free(f), -1 : -1);
	if (e)
		_strandcat(g, temp + a, c - a);
	else
		_strandclone(g, temp + a, c - a + 1);
	e += c - a;
	a = c;
	f = g;
	if (extent)
		*extent = e;
	*ab = f;
	return (e);
}
/**
 *interrupt_handler - blocks control + c
 *@int_numb: signal number
 *Return: ---
 */
void interrupt_handler(__attribute__((unused))int int_numb)
{
	output_string("\n");
	output_string("$ ");
	output_symbols(BUF_PURGE);
}
