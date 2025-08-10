/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:40:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 04:40:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables_internal.h"

t_var	*find_variable(char	*name)
{
	t_var	*temp;

	temp = ft_var(NULL, GET);
	if (!temp || !name)
		return (NULL);
	while (temp)
	{
		if (temp->name && ft_strcmp(temp->name, name) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_var	*make_varlist(t_var	*var)
{
	t_var	*temp;
	t_var	*varlist;

	if (!var || !var->name)
		return (NULL);
	temp = find_variable(var->name);
	if (temp)
	{
		free(temp->value);
		temp->value = ft_strdup(var->value);
	}
	else
	{
		temp = ft_var(NULL, GET);
		if (!temp)
		{
			temp = ft_var(var, SET);
			return (temp);
		}
		while (temp->next)
			temp = temp->next;
		temp->next = var;
	}
	varlist = ft_var(NULL, GET);
	return (varlist);
}

void	unset_variable(char *name)
{
	t_var	*var;
	t_var	*temp;
	t_var	*prev;

	var = ft_var(NULL, GET);
	if (!var || !name)
		return ;
	temp = var;
	prev = NULL;
	while (temp)
	{
		if (temp->name && ft_strcmp(temp->name, name) == 0)
			break ;
		prev = temp;
		temp = temp->next;
	}
	if (temp && temp->name && ft_strcmp(temp->name, name) == 0)
	{
		if (prev == NULL)
			ft_var(temp->next, SET);
		else
			prev->next = temp->next;
		dispose_var(temp);
	}
}

void	update_var_value(t_var *var, char *new_value)
{
	if (!var)
		return ;
	free(var->value);
	var->value = ft_strdup(new_value);
}
