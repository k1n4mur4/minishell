/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:30:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 17:48:29 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_internal.h"
#include "expander.h"
#include "sig.h"
#include <readline/readline.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void	write_heredoc_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static int	process_heredoc_line(int fd, char *line, int expand_vars)
{
	char	*processed_line;

	if (expand_vars)
	{
		processed_line = expand_heredoc_line(line);
		write_heredoc_line(fd, processed_line);
		free(processed_line);
	}
	else
	{
		write_heredoc_line(fd, line);
	}
	return (1);
}

int	read_heredoc_interactive(int fd, char *delimiter, int expand_vars)
{
	char	*line;

	if (g_interrupt_state == SIGINT)
	{
		g_interrupt_state = 0;
		return (0);
	}
	line = readline("> ");
	if (!line)
	{
		if (g_interrupt_state == SIGINT)
		{
			g_interrupt_state = 0;
			return (0);
		}
		return (0);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (0);
	}
	process_heredoc_line(fd, line, expand_vars);
	free(line);
	return (1);
}

int	read_heredoc_non_interactive(int fd, char *delimiter, int expand_vars)
{
	char	buffer[1024];
	char	*line;

	if (g_interrupt_state == SIGINT)
	{
		g_interrupt_state = 0;
		return (0);
	}
	if (!fgets(buffer, sizeof(buffer), stdin))
		return (0);
	line = ft_strtrim(buffer, "\n");
	if (!line)
		return (0);
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (0);
	}
	process_heredoc_line(fd, line, expand_vars);
	free(line);
	return (1);
}
