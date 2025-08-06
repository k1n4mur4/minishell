#include "exit_shell.h"

int	exit_shell(void)
{
	int	last_command_exit_value;
	
	varlist(NULL, FREE);
	last_command_exit_value = exit_value(0, GET);
	return	(last_command_exit_value);
}
