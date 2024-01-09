#include "shell_interface.h"
/**
 *main - entry point
 *@argct: argument count
 *@argvt: argument vector
 *Return: 0 for success otherwise 1
 */
int main(int argct, char **argvt)
{
	insight_t data[] = { DATA_INIT };
	int filedesc = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (filedesc)
			: "=r" (filedesc));
	if (argct == 2)
	{
		filedesc = open(argvt[1], O_RDONLY);
		if (filedesc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eprints(argvt[0]);
				_eprints(": 0: Can't open ");
				_eprints(argvt[1]);
				_eputc('\n');
				_eputc(BUF_PURGE);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = filedesc;
	}
	inhabit_ctxt_list(data);
	decipher_record(data);
	hash_table(data, argvt);
	return (EXIT_SUCCESS);
}
