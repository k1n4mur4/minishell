/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 23:31:37 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 22:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_internal.h"
#include <errno.h>
#include <string.h>

int	setup_redirections(t_redirect *redirects, t_exec_context *ctx)
{
	t_redirect	*current;

	if (!ctx)
		return (EXECUTION_FAILURE);
	init_exec_context(ctx);
	ctx->stdin_backup = dup(STDIN_FILENO);
	ctx->stdout_backup = dup(STDOUT_FILENO);
	if (ctx->stdin_backup == -1 || ctx->stdout_backup == -1)
	{
		perror("minishell");
		return (EXECUTION_FAILURE);
	}
	current = redirects;
	while (current)
	{
		if (setup_single_redirect(current) == EXECUTION_FAILURE)
		{
			restore_redirections(ctx);
			return (EXECUTION_FAILURE);
		}
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
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
			filename, strerror(errno));
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
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
			filename, strerror(errno));
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
