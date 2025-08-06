#include "variables.h"

t_varlist	*varlist(t_varlist *temp, t_type type)
{
	static t_varlist	*varlist = NULL;

	if (type == SET)
	{
		if (varlist)
			dispose_varlist(varlist);
		varlist = temp;
	}
	else if (type == GET)
		return (varlist);
	else if (type == ADD)
	{
		add_varlist(varlist, temp);
	}
	else if (type == FREE)
	{
		if (varlist)
			dispose_varlist(varlist);
		varlist = NULL;
	}
	return (varlist);
}
