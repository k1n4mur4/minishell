/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:45:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/12 22:45:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static int	open_heredoc_temp(char *template)
{
	int	fd;

	fd = open(template, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		unlink(template);
		free(template);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: heredoc");
		close(fd);
		unlink(template);
		free(template);
		return (-1);
	}
	close(fd);
	unlink(template);
	free(template);
	return (EXECUTION_SUCCESS);
}

static int	process_heredoc_line(char *line, char *delimiter)
{
	if (!line || g_interrupt_state == SIGINT)
	{
		if (line)
			free(line);
		if (!line)
			ft_dprintf(STDERR_FILENO, "%s: %s: %s",
				PROGRAM, WARNING, HEREDOC_WAR);
		return (1);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	write_heredoc_content(int fd, char *delimiter)
{
	char	*line;

	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (process_heredoc_line(line, delimiter))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	setup_signals();
	if (g_interrupt_state == SIGINT)
	{
		g_interrupt_state = 0;
		return (EXECUTION_FAILURE);
	}
	return (EXECUTION_SUCCESS);
}

int	redirect_heredoc(char *delimiter)
{
	char	*template;
	int		fd;

	if (!delimiter)
		return (EXECUTION_FAILURE);
	template = ft_strdup(TEMP_HERE_DOC);
	if (!template)
		return (EXECUTION_FAILURE);
	fd = ft_mkstemp(template);
	if (fd == -1)
	{
		free(template);
		return (EXECUTION_FAILURE);
	}
	if (write_heredoc_content(fd, delimiter) == EXECUTION_FAILURE)
	{
		close(fd);
		unlink(template);
		free(template);
		return (EXECUTION_FAILURE);
	}
	close(fd);
	return (open_heredoc_temp(template));
}
