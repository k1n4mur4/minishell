/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 23:31:37 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 16:10:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_internal.h"
#include <errno.h>
#include <string.h>

static int	setup_backup_fds(t_exec_context *ctx)
{
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
	return (EXECUTION_SUCCESS);
}

static int	handle_input_redirections(t_redirect *redirects)
{
	t_redirect	*last_input;

	last_input = find_last_input_redirect(redirects);
	if (last_input && last_input->instruction == r_input_direction
		&& handle_input_redirect(last_input->redirectee.filename->word)
		== EXECUTION_FAILURE)
		return (EXECUTION_FAILURE);
	return (EXECUTION_SUCCESS);
}

int	setup_redirections(t_redirect *redirects, t_exec_context *ctx)
{
	if (setup_backup_fds(ctx) == EXECUTION_FAILURE)
		return (EXECUTION_FAILURE);
	if (process_all_redirections(redirects, ctx) == EXECUTION_FAILURE)
	{
		restore_redirections(ctx);
		return (EXECUTION_FAILURE);
	}
	if (handle_input_redirections(redirects) == EXECUTION_FAILURE)
	{
		restore_redirections(ctx);
		return (EXECUTION_FAILURE);
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
