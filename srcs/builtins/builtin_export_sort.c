/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_sort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 20:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	count_vars(t_var *list)
{
	int		count;
	t_var	*current;

	count = 0;
	current = list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	sort_var_array(t_var **arr, int count)
{
	int		i;
	int		j;
	t_var	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(arr[j]->name, arr[j + 1]->name) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

t_var	**create_var_array(int count)
{
	t_var	**var_array;
	t_var	*current;
	int		i;

	var_array = malloc(sizeof(t_var *) * count);
	if (!var_array)
		return (NULL);
	i = 0;
	current = ft_var(NULL, GET);
	while (current && i < count)
	{
		var_array[i] = current;
		current = current->next;
		i++;
	}
	return (var_array);
}
