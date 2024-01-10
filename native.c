#include "shell_interface.h"
/**
 *_myleave - exits the interface
 *@data: structure
 *Return: exit eith a status
 */
int _myleave(insight_t *data)
{
	int a;

	if (data->argv[1])
	{
		a = _errstrtol(data->argv[1]);
		if (a == -1)
		{
			data->status = 2;
			print_flaw(data, "Illegal number: ");
			_eprints(data->argv[1]);
			_eputc('\n');
			return (1);
		}
		data->err_num = _errstrtol(data->argv[1]);
		return (-2);
	}
	data->err_num = -1;
	return (-2);
}
/**
 *_myworkingdir - changes current directory
 *@data: structure
 *Return: 0 Always
 */
int _myworkingdir(insight_t *data)
{
	char *a, *b, temp[1024];
	int change_dir;

	a = getcwd(temp, 1024);
	if (!a)
		output_string("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		b = _getctxt(data, "HOME=");
		if (!b)
			change_dir = chdir((b = _getctxt(data, "PWD=")) ?
					b : "/");
		else
			change_dir = chdir(b);
	}
	else if (strand_compare(data->argv[1], "-") == 0)
	{
		if (!_getctxt(data, "OLDPWD="))
		{
			output_string(a);
			output_symbols('\n');
			return (1);
		}
		output_string(_getctxt(data, "OLDPWD=")), output_symbols('\n');
		change_dir = chdir((b = _getctxt(data, "OLDPWD=")) ?
				dir : "/");
	}
	else
		chande_dir = chdir(data->argv[1]);
	if (change_dir == -1)
	{
		print_flaw(data, "can't cd to ");
		_eprints(data->argv[1]), _eputc('\n');
	}
	else
	{
		set_ambiance(data, "OLDPWD", _getctxt(data, "PWD="));
		set_ambiance(data, "PWD", getcwd(temp, 1024));
	}
	return (0);
}
/**
 *_mysupport - changes the working directory
 *@data: structure
 *Return: 0 Always
 */
int _mysupport(insight_t *data)
{
	char **a;

	a = data->argv;
	output_string("help call works. Function not yet implemented \n");
	if (0)
		output_string(a);
	return (0);
}
