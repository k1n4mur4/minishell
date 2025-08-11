/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 22:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_internal.h"
#include <readline/readline.h>
#include <stdio.h>

void	write_heredoc_line(int pipefd, char *line)
{
	write(pipefd, line, ft_strlen(line));
	write(pipefd, "\n", 1);
}

int	read_heredoc_interactive(int pipefd, char *delimiter)
{
	char	*line;

	line = readline("> ");
	if (!line || ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (0);
	}
	write_heredoc_line(pipefd, line);
	free(line);
	return (1);
}

int	read_heredoc_non_interactive(int pipefd, char *delimiter)
{
	char	buffer[1024];
	char	*line;

	if (!fgets(buffer, sizeof(buffer), stdin))
		return (0);
	line = ft_strtrim(buffer, "\n");
	if (!line || ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (0);
	}
	write_heredoc_line(pipefd, line);
	free(line);
	return (1);
}

int	handle_heredoc(char *delimiter)
{
	int	pipefd[2];

	if (!delimiter)
		return (EXECUTION_FAILURE);
	if (setup_heredoc_pipe(pipefd) != EXECUTION_SUCCESS)
		return (EXECUTION_FAILURE);
	read_heredoc_input(pipefd[1], delimiter);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("minishell");
		close(pipefd[0]);
		return (EXECUTION_FAILURE);
	}
	close(pipefd[0]);
	return (EXECUTION_SUCCESS);
}
