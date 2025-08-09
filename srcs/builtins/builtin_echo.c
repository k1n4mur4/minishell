/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:38:21 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 05:38:22 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "shell.h"

int	builtin_echo(t_word_list *args)
{
	t_word_list	*current;
	int			n_flag;

	n_flag = 0;
	if (!args)
		return (EXECUTION_FAILURE);
	current = args->next;
	if (current && current->word && current->word->word)
	{
		if (ft_strcmp(current->word->word, "-n") == 0)
		{
			n_flag = 1;
			current = current->next;
		}
	}
	while (current)
	{
		if (current->word && current->word->word)
		{
			write(STDOUT_FILENO, current->word->word,
				ft_strlen(current->word->word));
			if (current->next && current->next->word
				&& current->next->word->word)
				write(STDOUT_FILENO, " ", 1);
		}
		current = current->next;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (EXECUTION_SUCCESS);
}