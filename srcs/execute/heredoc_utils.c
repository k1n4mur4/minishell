/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:30:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 05:53:56 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "shell.h"

void	read_heredoc_input(int write_fd, char *delimiter)
{
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			if (!read_heredoc_interactive(write_fd, delimiter))
				break ;
		}
		else
		{
			if (!read_heredoc_non_interactive(write_fd, delimiter))
				break ;
		}
	}
}

int	setup_heredoc_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("minishell");
		return (EXECUTION_FAILURE);
	}
	return (EXECUTION_SUCCESS);
}
