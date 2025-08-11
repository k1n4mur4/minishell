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
#include "redirect_internal.h"
#include <fcntl.h>

char	*create_temp_heredoc_file(void)
{
	char	*template;
	char	*filename;
	int		fd;

	template = ft_strdup("/tmp/heredocXXXXXX");
	if (!template)
		return (NULL);
	fd = ft_mkstemp(template);
	if (fd == -1)
	{
		free(template);
		return (NULL);
	}
	close(fd);
	filename = ft_strdup(template);
	free(template);
	return (filename);
}

int	should_expand_variables(char *delimiter)
{
	int	i;

	if (!delimiter)
		return (0);
	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

void	read_heredoc_input(int write_fd, char *delimiter)
{
	int	expand_vars;

	expand_vars = should_expand_variables(delimiter);
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			if (!read_heredoc_interactive(write_fd, delimiter, expand_vars))
				break ;
		}
		else
		{
			if (!read_heredoc_non_interactive(write_fd, delimiter, expand_vars))
				break ;
		}
	}
}

char	*expand_heredoc_line(char *line)
{
	char	*expanded;

	if (!line)
		return (NULL);
	expanded = expand_string(line, 0);
	if (expanded)
		return (expanded);
	return (ft_strdup(line));
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
