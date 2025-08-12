/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:35:42 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 15:04:57 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(char *command)
{
	if (!command)
		return (0);
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_simple_com *cmd)
{
	char	*command;

	if (!cmd || !cmd->words || !cmd->words->word || !cmd->words->word->word)
		return (EXECUTION_FAILURE);
	command = cmd->words->word->word;
	if (ft_strcmp(command, "echo") == 0)
		return (builtin_echo(cmd->words));
	if (ft_strcmp(command, "cd") == 0)
		return (builtin_cd(cmd->words));
	if (ft_strcmp(command, "pwd") == 0)
		return (builtin_pwd(cmd->words));
	if (ft_strcmp(command, "export") == 0)
		return (builtin_export(cmd->words));
	if (ft_strcmp(command, "unset") == 0)
		return (builtin_unset(cmd->words));
	if (ft_strcmp(command, "env") == 0)
		return (builtin_env(cmd->words));
	if (ft_strcmp(command, "exit") == 0)
		return (builtin_exit(cmd->words));
	return (EXECUTION_FAILURE);
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
