/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                 :+:      :+:    :+:   */
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

int	is_output_redirect(t_redirect *redirect)
{
	return (redirect && (redirect->instruction == r_output_direction
			|| redirect->instruction == r_appending_to));
}

t_redirect	*find_last_input_redirect(t_redirect *redirects)
{
	t_redirect	*last;
	t_redirect	*current;

	last = NULL;
	current = redirects;
	while (current)
	{
		if (current->instruction == r_input_direction
			|| current->instruction == r_reading_until)
			last = current;
		current = current->next;
	}
	return (last);
}

int	open_output_file(char *filename, int append)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (open(filename, flags, 0644));
}

t_redirect	*find_first_output_redirect(t_redirect *redirects)
{
	t_redirect	*current;

	current = redirects;
	while (current)
	{
		if (is_output_redirect(current))
			return (current);
		current = current->next;
	}
	return (NULL);
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
