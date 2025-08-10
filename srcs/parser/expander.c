/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:10:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 07:10:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"

char	*get_variable_value(char *name)
{
	t_var	*var;
	char	*exit_status_str;

	if (!name)
		return (ft_strdup(""));
	if (ft_strcmp(name, "?") == 0)
	{
		exit_status_str = ft_itoa(exit_value(0, GET));
		return (exit_status_str);
	}
	var = find_variable(name);
	if (var && var->value)
		return (ft_strdup(var->value));
	return (ft_strdup(""));
}

char	*expand_string(char *str, int in_double_quotes)
{
	char	*result;

	if (!str)
		return (NULL);
	if (ft_strchr(str, '$') == NULL)
		return (ft_strdup(str));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (process_expansion_loop(result, str, in_double_quotes));
}

void	expand_variables(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == cm_simple && cmd->simple)
	{
		expand_word_list(cmd->simple->words);
		expand_redirects(cmd->simple->redirects);
	}
	else if (cmd->type == cm_connection && cmd->connection)
	{
		expand_variables(cmd->connection->first);
		expand_variables(cmd->connection->second);
	}
}
