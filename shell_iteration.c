#include "shell_interface.h"
/**
 *hash_table - main loop
 *@data: parameter
 *@argvt: argument vector
 *Return: 0 on success otherwise -1
 */
int hash_table(insight_t *data, char **argvt)
{
	ssize_t a = 0;
	int b = 0;

	while (a != -1 && b != -2)
	{
		clear_insight(data);
		if (responsive(data))
			output_string("$ ");
		_eputc(BUF_PURGE);
		a = get_dataentry(data);
		if (a != -1)
		{
			set_insight(data, argvt);
			b = find_native(data);
			if (b == -1)
				find_prompt(data);
		}
		else if (responsive(data))
			output_symbols('\n');
		free_insight(data, 0);
	}
	write_record(data);
	free_insight(data, 1);
	if (!responsive(data) && data->status)
		return (data->status);
	if (b == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (b);
}
/**
 *find_native - finds intrinsic commands
 *@data: parameter
 *Return: -1 if command not found
 */
int find_native(insight_t *data)
{
	int a, b = -1;
	embedded_table c[] = {
		{"exit", _myleave},
		{"env", _myctxt},
		{"help", _mysupport},
		{"history", my_record},
		{"setenv", _mysetctxt},
		{"unsetenv", _myunsetctxt},
		{"cd", _myworkingdir},
		{"alias", my_sobriquet},
		{NULL, NULL}
	};
	for (a = 0; c[a].type; a++)
		if (strand_compare(data->argv[0], c[a].type) == 0)
		{
			data->line_count++;
			b = c[a].func(data);
			break;
		}
	return (b);
}
/**
 *find_prompt - finds commands
 *@data: parameter
 *Return: ---
 */
void find_prompt(insight_t *data)
{
	char *route = NULL;
	int a, b;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (a = 0, b = 0; data->arg[a]; a++)
		if (!is_divider(data->arg[a], " \t\n"))
			b++;
	if (!b)
		return;
	route = find_route(data, _getctxt(data, "PATH="), data->argv[0]);
	if (route)
	{
		data->path = route;
		fork_prompt(data);
	}
	else
	{
		if ((responsive(data) || _getctxt(data, "PATH=")
					|| data->argv[0][0] == '/') &&
				is_prompt(data, data->argv[0]))
			fork_prompt(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_flaw(data, "not found\n");
		}
	}
}
/**
 *fork_prompt - forks an executable thread
 *@data: parameter
 *Return: ---
 */
void fork_prompt(insight_t *data)
{
	pid_t a;

	a = fork();
	if (a == -1)
	{
		/* TODO: PLACE FLAW FUNCTION */
		perror("Error:");
		return;
	}
	if (a == 0)
	{
		if (execve(data->path, data->argv, get_context(data)) == -1)
		{
			free_insight(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: FLAW FUNCTION */
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_flaw(data, "Permission denied\n");
		}
	}
}
