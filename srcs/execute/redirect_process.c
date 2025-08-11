/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:10:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 16:10:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_internal.h"
#include <errno.h>
#include <string.h>

static int	handle_output_redirect_item(t_redirect *current, t_redirect *last)
{
	int	fd;

	fd = open_output_file(current->redirectee.filename->word,
			current->instruction == r_appending_to);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
			current->redirectee.filename->word, strerror(errno));
		return (EXECUTION_FAILURE);
	}
	if (current == last)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			close(fd);
			return (EXECUTION_FAILURE);
		}
	}
	close(fd);
	return (EXECUTION_SUCCESS);
}

int	process_all_redirections(t_redirect *redirects, t_exec_context *ctx)
{
	t_redirect	*current;
	t_redirect	*last_output;

	(void)ctx;
	last_output = find_first_output_redirect(redirects);
	current = redirects;
	while (current)
	{
		if (is_output_redirect(current))
		{
			if (handle_output_redirect_item(current, last_output)
				== EXECUTION_FAILURE)
				return (EXECUTION_FAILURE);
		}
		else if (current->instruction == r_reading_until)
		{
			if (handle_heredoc(current->here_doc_eof) == EXECUTION_FAILURE)
				return (EXECUTION_FAILURE);
		}
		current = current->next;
	}
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
