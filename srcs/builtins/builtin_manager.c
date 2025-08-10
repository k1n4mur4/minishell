/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:35:42 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 05:53:59 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "shell.h"

static t_builtin	g_builtins[] = {
{"echo", builtin_echo},
{"cd", builtin_cd},
{"pwd", builtin_pwd},
{"export", builtin_export},
{"unset", builtin_unset},
{"env", builtin_env},
{"exit", builtin_exit},
{NULL, NULL}
};

int	is_builtin(char *command)
{
	int	i;

	if (!command)
		return (0);
	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(command, g_builtins[i].name) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	find_builtin_index(char *command)
{
	int	i;

	if (!command)
		return (-1);
	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(command, g_builtins[i].name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	execute_builtin(t_simple_com *cmd)
{
	int	index;

	if (!cmd || !cmd->words || !cmd->words->word || !cmd->words->word->word)
		return (EXECUTION_FAILURE);
	index = find_builtin_index(cmd->words->word->word);
	if (index == -1)
		return (EXECUTION_FAILURE);
	return (g_builtins[index].func(cmd->words));
}

int	count_args(t_word_list *args)
{
	int			count;
	t_word_list	*current;

	count = 0;
	current = args;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
