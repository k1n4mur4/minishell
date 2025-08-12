/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:46:31 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 04:09:07 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	process_unset_arg(char *arg)
{
	if (!validate_identifier(arg))
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: unset: `%s': not a valid identifier\n", arg);
		return (EXECUTION_FAILURE);
	}
	unset_variable(arg);
	return (EXECUTION_SUCCESS);
}

int	builtin_unset(t_word_list *args)
{
	t_word_list	*current;
	int			exit_status;

	if (!args)
		return (EXECUTION_FAILURE);
	if (count_args(args) == 1)
		return (EXECUTION_SUCCESS);
	exit_status = EXECUTION_SUCCESS;
	current = args->next;
	while (current)
	{
		if (current->word && current->word->word)
		{
			if (process_unset_arg(current->word->word) == EXECUTION_FAILURE)
				exit_status = EXECUTION_FAILURE;
		}
		current = current->next;
	}
	return (exit_status);
}
