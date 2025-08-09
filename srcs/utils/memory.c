/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:32:17 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 05:32:18 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "variables.h"

void	free_argv_array(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_envp_array(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	count_word_list(t_word_list *words)
{
	int			count;
	t_word_list	*current;

	count = 0;
	current = words;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	count_variables(void)
{
	int		count;
	t_var	*current;

	count = 0;
	current = ft_var(NULL, GET);
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}