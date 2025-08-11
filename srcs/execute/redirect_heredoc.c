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
#include "expander.h"
#include "sig.h"
#include <readline/readline.h>
#include <stdio.h>
#include <fcntl.h>

static void	cleanup_heredoc_file(char *temp_file)
{
	if (temp_file)
	{
		unlink(temp_file);
		free(temp_file);
	}
}

static int	setup_heredoc_write(char *delimiter, char *temp_file)
{
	int	fd;

	setup_heredoc_signals();
	fd = open(temp_file, O_WRONLY);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		cleanup_heredoc_file(temp_file);
		setup_signals();
		return (-1);
	}
	read_heredoc_input(fd, delimiter);
	close(fd);
	setup_signals();
	return (0);
}

static int	setup_heredoc_read(char *temp_file)
{
	int	fd;

	fd = open(temp_file, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		cleanup_heredoc_file(temp_file);
		return (EXECUTION_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: heredoc");
		close(fd);
		cleanup_heredoc_file(temp_file);
		return (EXECUTION_FAILURE);
	}
	close(fd);
	return (EXECUTION_SUCCESS);
}

int	handle_heredoc(char *delimiter)
{
	char	*temp_file;

	if (!delimiter)
		return (EXECUTION_FAILURE);
	temp_file = create_temp_heredoc_file();
	if (!temp_file)
	{
		perror("minishell: heredoc");
		return (EXECUTION_FAILURE);
	}
	if (setup_heredoc_write(delimiter, temp_file) == -1)
		return (EXECUTION_FAILURE);
	if (g_interrupt_state == SIGINT)
	{
		g_interrupt_state = 0;
		cleanup_heredoc_file(temp_file);
		return (EXECUTION_FAILURE);
	}
	if (setup_heredoc_read(temp_file) != EXECUTION_SUCCESS)
		return (EXECUTION_FAILURE);
	cleanup_heredoc_file(temp_file);
	return (EXECUTION_SUCCESS);
}
