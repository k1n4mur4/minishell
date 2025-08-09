/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:46:31 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 05:46:32 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "variables.h"
#include "shell.h"

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
			if (!validate_identifier(current->word->word))
			{
				ft_dprintf(STDERR_FILENO,
					"minishell: unset: `%s': not a valid identifier\n",
					current->word->word);
				exit_status = EXECUTION_FAILURE;
			}
			else
				unset_variable(current->word->word);
		}
		current = current->next;
	}
	return (exit_status);
}