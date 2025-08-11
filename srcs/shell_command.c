/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:40:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 05:46:48 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	process_command_line(char *line)
{
	t_token		*tokens;
	t_command	*cmd;

	if (!line || !*line)
		return ;
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
		else
		{
			exit_value(EXECUTION_FAILURE, SET);
		}
		free_tokens(tokens);
	}
}
