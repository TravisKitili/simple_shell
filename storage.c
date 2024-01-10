#include "shell_interface.h"
/**
 *bcrisp - frees a pointer
 *@ptad: pointer address
 *Return: 1 otherwise 0
 */
int bcrisp(void **ptad)
{
	if (ptad && *ptad)
	{
		free(*ptad);
		*ptad = NULL;
		return (1);
	}
	return (0);
}
