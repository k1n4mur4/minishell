/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:49:39 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/05 23:07:32 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_option_v(void)
{
	ft_printf("# Configuration file for interactive Minishell sessions\n\n"
		"# Exit early if not in an interactive shell\n"
		"[ -z \"$PS1\" ] && return\n\n"
		"# Set up prompt (compatible with Minishell constraints)\n"
		"PS1='\\u@\\h:\\w\\$ '\n\n"
		"# Display a simple message about using Minishell\n"
		"echo \"Welcome to Minishell - a simple shell created as part of 42 "
		"project.\"\n\n# Disable advanced bash features not "
		"supported in Minishell\n"
		"unset PROMPT_COMMAND\nunset HISTFILE\nunset BASH_COMPLETION\n"
		"unset command_not_found_handle\n\n"
		"# Avoid sourcing system-wide bash completion or additional scripts\n"
		"# as Minishell does not support these features\n\n"
		"# Display sudo hint (optional)\n"
		"if [ ! -e \"$HOME/.sudo_as_admin_successful\" ] && [ ! -e \"$HOME/."
		"hushlogin\" ]; then\n"
		"\tcase \" $(groups) \" in *\\ admin\\ *|*\\ sudo\\ *)\n"
		"\tif [ -x /usr/bin/sudo ]; then\n\tcat <<-EOF\n"
		"\tTo run a command as administrator (user \\\"root\\\"), use \\\""
		"sudo <command>\\\".\n"
		"\tThis hint is shown because you're using Minishell,"
		" which simulates basic bash behavior.\n"
		"\tEOF\n\tfi\n\tesac\nfi\n");
	return (0);
}

int	shell(int argc, char **argv, char **envp)
{
	if (argc == 1 && ft_strcmp(argv[1], "-v") == 0)
		handle_option_v();
	else if (argc > 1)
	{
		if (ft_strcmp(argv[1], "--version") == 0)
		{
			handle_option_version();
			return (0);
		}
		ft_dprintf(STDERR_FILENO,
			"%s: %s: No such file or directory\n",
			ENAME, argv[1]);
		return (127);
	}
	initialize_enviroment(envp);
	shell_initialize();
	if (isatty(STDIN_FILENO))
		reader_loop();
	else
		execute_stdin_commands();
	exit_shell();
	return (exit_value(0, GET));
}
