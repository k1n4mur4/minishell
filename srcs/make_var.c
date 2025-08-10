/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:40:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 05:53:21 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var.h"

t_var	*alloc_shell_var(void)
{
	t_var	*temp;

	temp = (t_var *)ft_calloc(sizeof(t_var), 1);
	if (!temp)
		return (NULL);
	temp->name = NULL;
	temp->value = NULL;
	temp->next = NULL;
	return (temp);
}

t_var	*make_bare_var(char *name)
{
	t_var	*temp;

	if (!name)
		return (NULL);
	temp = alloc_shell_var();
	if (!temp)
		return (NULL);
	if (*name)
	{
		temp->name = ft_strdup(name);
		if (!temp->name)
		{
			free(temp);
			return (NULL);
		}
	}
	return (temp);
}

t_var	*make_var_value(t_var *v, char *value)
{
	if (v)
	{
		if (v->value)
			free(v->value);
		v->value = ft_strdup(value);
	}
	return (v);
}

t_var	*make_var(char *name, char *value)
{
	t_var	*temp;

	temp = make_bare_var(name);
	if (!temp)
		return (NULL);
	return (make_var_value(temp, value));
}
