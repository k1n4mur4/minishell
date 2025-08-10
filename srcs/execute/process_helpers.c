/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:30:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 21:30:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "shell.h"
#include <unistd.h>
#include <stdlib.h>

void	free_partial_argv(char **argv, int count)
{
	while (--count >= 0)
		free(argv[count]);
	free(argv);
}

int	fill_argv_array(char **argv, t_word_list *words, int count)
{
	t_word_list	*current;
	int			i;

	current = words;
	i = 0;
	while (current && i < count)
	{
		argv[i] = ft_strdup(current->word->word);
		if (!argv[i])
			return (i);
		current = current->next;
		i++;
	}
	return (-1);
}

int	fill_envp_array(char **envp, t_var *vars, int count)
{
	t_var	*current;
	char	*env_str;
	int		i;

	current = vars;
	i = 0;
	while (current && i < count)
	{
		if (current->name && current->value)
		{
			env_str = build_env_string(current->name, current->value);
			if (!env_str)
				return (-1);
			envp[i++] = env_str;
		}
		current = current->next;
	}
	return (i);
}

char	*search_in_paths(char **paths, char *command)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = build_path(paths[i], command);
		if (full_path && access(full_path, X_OK) == 0)
			return (full_path);
		if (full_path)
			free(full_path);
		i++;
	}
	return (NULL);
}
