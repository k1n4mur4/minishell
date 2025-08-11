/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:10:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 22:10:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"

char	*handle_no_var_name(char *result, int *i)
{
	char	*temp;

	temp = ft_strjoin(result, "$");
	if (!temp)
		return (result);
	free(result);
	(*i)++;
	return (temp);
}

char	*append_var_value(char *result, char *var_value)
{
	char	*temp;

	temp = ft_strjoin(result, var_value);
	if (!temp)
	{
		free(var_value);
		return (result);
	}
	free(result);
	free(var_value);
	return (temp);
}

char	*handle_special_variable(char *str, int *i)
{
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	return (NULL);
}

char	*allocate_var_name(char *str, int start, int len)
{
	char	*var_name;

	if (len == 0)
		return (NULL);
	var_name = (char *)malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, &str[start], len + 1);
	return (var_name);
}
