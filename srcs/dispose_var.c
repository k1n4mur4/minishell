#include "variables.h"
#include "dispose_var.h"
#include <stdlib.h>

void	dispose_var(t_shell_var *var)
{
	if (var)
	{
		if (var->name)
			free(var->name);
		if (var->value)
			free(var->value);
		free(var);
	}
}

void	dispose_varlist(t_varlist *varlist)
{
	t_shell_var	**temp;

	if (varlist)
	{
		if (varlist->list)
		{
			temp = varlist->list;
			while (*temp)
			{
				dispose_var(*temp);
				temp++;
			}
			free(varlist->list);
		}
		free(varlist);
	}
}
