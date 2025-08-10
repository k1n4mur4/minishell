/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:49:39 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 04:30:58 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <readline/readline.h>
#include <readline/history.h>

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

static char	*read_input_line(void)
{
	char	*prompt;
	char	*line;

	g_interrupt_state = 0;
	prompt = get_prompt();
	line = readline(prompt);
	if (!line)
		ft_printf("exit\n");
	return (line);
}

static int	reader_loop(void)
{
	char	*line;

	setup_signals();
	while (1)
	{
		line = read_input_line();
		if (!line)
			break ;
		if (*line)
			add_history(line);
		process_command_line(line);
		free(line);
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
