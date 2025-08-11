/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:40:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 05:47:02 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables_internal.h"

t_var	*create_var(char *str)
{
	t_var	*var;
	char	*name;
	char	*value;
	char	*equal;

	equal = ft_strchr(str, '=');
	if (equal)
	{
		name = ft_strndup(str, equal - str);
		value = ft_strdup(equal + 1);
	}
	else
	{
		name = ft_strdup(str);
		value = NULL;
	}
	var = make_var(name, value);
	if (name)
		free(name);
	if (value)
		free(value);
	return (var);
}
