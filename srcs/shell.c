/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:49:39 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/13 03:20:20 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	handle_command_option(char **argv, char **env)
{
	int	exit_status;

	if (!argv[2])
		return (EXECUTION_FAILURE);
	initialize_shell_variables(env);
	shell_initialize();
	process_command_line(argv[2]);
	exit_status = exit_value(EXECUTION_SUCCESS, GET);
	return (exit_status);
}

static int	execute_stdin_commands(void)
{
	char	*line;

	line = readline("");
	while (line != NULL)
	{
		process_command_line(line);
		free(line);
		line = readline("");
	}
	return (exit_value(EXECUTION_SUCCESS, GET));
}

int	main(int argc, char **argv, char **env)
{
	if (argc >= 3 && ft_strcmp(argv[1], "-c") == 0)
		return (handle_command_option(argv, env));
	if (argc > 1)
	{
		if (ft_strcmp(argv[1], "--version") == 0)
		{
			show_shell_version(1);
			exit (EXECUTION_SUCCESS);
		}
		ft_dprintf(STDERR_FILENO,
			"%s: %s: No such file or directory\n",
			PROGRAM, argv[1]);
		return (127);
	}
	initialize_shell_variables(env);
	shell_initialize();
	if (isatty(STDIN_FILENO))
		reader_loop();
	else
		execute_stdin_commands();
	exit_shell();
	return (exit_value(EXECUTION_SUCCESS, GET));
}
