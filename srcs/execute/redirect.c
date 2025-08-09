/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:51:42 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 05:51:43 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "shell.h"
#include <fcntl.h>
#include <readline/readline.h>

int	setup_redirections(t_redirect *redirects, t_exec_context *ctx)
{
	t_redirect	*current;

	if (!ctx)
		return (EXECUTION_FAILURE);
	ctx->stdin_backup = dup(STDIN_FILENO);
	ctx->stdout_backup = dup(STDOUT_FILENO);
	ctx->stderr_backup = dup(STDERR_FILENO);
	if (ctx->stdin_backup == -1 || ctx->stdout_backup == -1
		|| ctx->stderr_backup == -1)
		return (EXECUTION_FAILURE);
	current = redirects;
	while (current)
	{
		if (setup_single_redirect(current) != EXECUTION_SUCCESS)
			return (EXECUTION_FAILURE);
		current = current->next;
	}
	return (EXECUTION_SUCCESS);
}

int	restore_redirections(t_exec_context *ctx)
{
	if (!ctx)
		return (EXECUTION_FAILURE);
	if (ctx->stdin_backup != -1)
	{
		dup2(ctx->stdin_backup, STDIN_FILENO);
		close(ctx->stdin_backup);
	}
	if (ctx->stdout_backup != -1)
	{
		dup2(ctx->stdout_backup, STDOUT_FILENO);
		close(ctx->stdout_backup);
	}
	if (ctx->stderr_backup != -1)
	{
		dup2(ctx->stderr_backup, STDERR_FILENO);
		close(ctx->stderr_backup);
	}
	return (EXECUTION_SUCCESS);
}

int	setup_single_redirect(t_redirect *redir)
{
	if (!redir)
		return (EXECUTION_FAILURE);
	if (redir->instruction == r_input_direction)
		return (handle_input_redirect(redir->redirectee.filename->word));
	else if (redir->instruction == r_output_direction)
		return (handle_output_redirect(redir->redirectee.filename->word, 0));
	else if (redir->instruction == r_appending_to)
		return (handle_output_redirect(redir->redirectee.filename->word, 1));
	else if (redir->instruction == r_reading_until)
		return (handle_heredoc(redir->here_doc_eof));
	return (EXECUTION_FAILURE);
}

int	handle_input_redirect(char *filename)
{
	int	fd;

	if (!filename)
		return (EXECUTION_FAILURE);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (EXECUTION_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell");
		close(fd);
		return (EXECUTION_FAILURE);
	}
	close(fd);
	return (EXECUTION_SUCCESS);
}

int	handle_output_redirect(char *filename, int append)
{
	int	fd;
	int	flags;

	if (!filename)
		return (EXECUTION_FAILURE);
	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (EXECUTION_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		close(fd);
		return (EXECUTION_FAILURE);
	}
	close(fd);
	return (EXECUTION_SUCCESS);
}

static void	write_heredoc_line(int pipefd, char *line)
{
	write(pipefd, line, ft_strlen(line));
	write(pipefd, "\n", 1);
}

static int	read_heredoc_interactive(int pipefd, char *delimiter)
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

static int	read_heredoc_non_interactive(int pipefd, char *delimiter)
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
	if (pipe(pipefd) == -1)
	{
		perror("minishell");
		return (EXECUTION_FAILURE);
	}
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			if (!read_heredoc_interactive(pipefd[1], delimiter))
				break ;
		}
		else
		{
			if (!read_heredoc_non_interactive(pipefd[1], delimiter))
				break ;
		}
	}
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