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

static char	*get_prompt(void)
{
	t_var	*ps1_var;
	char	*prompt;

	ps1_var = find_variable("PS1");
	if (ps1_var && ps1_var->value)
		prompt = ps1_var->value;
	else
		prompt = "minishell$ ";
	return (prompt);
}

static void	shell_initialize(void)
{
	t_var	*ps1_var;

	ps1_var = find_variable("PS1");
	if (!ps1_var)
	{
		ps1_var = make_var("PS1", "minishell$ ");
		if (ps1_var)
			make_varlist(ps1_var);
	}
}

static int	reader_loop(void)
{
	char		*line;
	char		*prompt;
	t_token		*tokens;
	t_command	*cmd;

	setup_signals();
	while (1)
	{
		g_interrupt_state = 0;
		prompt = get_prompt();
		line = readline(prompt);
		if (!line)
		{
			ft_printf("exit\n");
			break ;
		}
		if (*line)
		{
			add_history(line);
			tokens = tokenize_input(line);
			if (tokens)
			{
				cmd = parse_command_line(tokens);
				if (cmd)
				{
					expand_variables(cmd);
					execute_command(cmd);
					free_command(cmd);
				}
				free_tokens(tokens);
			}
		}
		free(line);
	}
	return (exit_value(EXECUTION_SUCCESS, GET));
}

int	main(int argc, char **argv, char **env)
{
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
	{
		char	*line;
		t_token	*tokens;
		t_command *cmd;
		
		while ((line = readline("")) != NULL)
		{
			if (*line)
			{
				tokens = tokenize_input(line);
				if (tokens)
				{
					cmd = parse_command_line(tokens);
					if (cmd)
					{
						expand_variables(cmd);
						execute_command(cmd);
						free_command(cmd);
					}
					free_tokens(tokens);
				}
			}
			free(line);
		}
	}
	exit_shell();
	return (exit_value(EXECUTION_SUCCESS, GET));
}
