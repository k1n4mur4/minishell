#include "eval.h"


// int	read_command(void)
// {
// 	SHELL_VAR *tmout_var;
// 	int tmout_len, result;
// 	SigHandler	*old_alrm;

// 	set_current_prompt_level (1);
// 	global_command = (COMMAND *)NULL;

// 	/* Only do timeouts if interactive. */
// 	tmout_var = (SHELL_VAR *)NULL;
// 	tmout_len = 0;
// 	old_alrm = (SigHandler *)NULL;

// 	if (interactive)
// 	{
// 		tmout_var = find_variable ("TMOUT");

// 		if (tmout_var && var_isset (tmout_var))
// 		{
// 			tmout_len = atoi (value_cell (tmout_var));
// 			if (tmout_len > 0)
// 				{
// 					old_alrm = set_signal_handler (SIGALRM, alrm_catcher);
// 					alarm (tmout_len);
// 				}
// 		}
// 	}

// 	QUIT;

// 	current_command_line_count = 0;
// 	result = parse_command();
// 	if (interactive && tmout_var && (tmout_len > 0))
// 	{
// 		alarm(0);
// 		set_signal_handler(SIGALRM, old_alrm);
// 	}
// 	return (result);
// }
