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

int	redirect_heredoc(char *delimiter)
{
	char	*template;
	char	*line;
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
	while (1)
	{
		line = readline("> ");
		if (!line || g_interrupt_state == SIGINT)
		{
			if (line)
				free(line);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	if (g_interrupt_state == SIGINT)
	{
		g_interrupt_state = 0;
		unlink(template);
		free(template);
		return (EXECUTION_FAILURE);
	}
	return (open_heredoc_temp(template));
}
