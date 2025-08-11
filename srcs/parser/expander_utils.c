/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:10:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 22:10:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"

char	*extract_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*special_var;

	(*i)++;
	start = *i;
	special_var = handle_special_variable(str, i);
	if (special_var)
		return (special_var);
	if (!str[*i] || (!ft_isalnum(str[*i]) && str[*i] != '_'))
	{
		(*i)--;
		return (NULL);
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	return (allocate_var_name(str, start, len));
}

int	should_expand_in_quotes(char c, int in_single_quotes)
{
	if (in_single_quotes)
		return (0);
	return (c == '$');
}

char	*append_string_before_variable(char *result, char *str, int start,
		int i)
{
	char	*temp;
	char	*new_result;

	if (i <= start)
		return (result);
	temp = ft_substr(str, start, i - start);
	if (!temp)
		return (result);
	new_result = ft_strjoin(result, temp);
	if (!new_result)
	{
		free(temp);
		return (result);
	}
	free(result);
	free(temp);
	return (new_result);
}

char	*expand_variable_at_position(char *result, char *str, int *i)
{
	char	*var_name;
	char	*var_value;

	var_name = extract_var_name(str, i);
	if (!var_name)
		return (handle_no_var_name(result, i));
	var_value = get_variable_value(var_name);
	if (var_value)
		result = append_var_value(result, var_value);
	free(var_name);
	return (result);
}
