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

#include "expander.h"

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

static char	*extract_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	(*i)++;
	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (ft_strdup(""));
	var_name = (char *)malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, &str[start], len + 1);
	return (var_name);
}

static int	should_expand_in_quotes(char c, int in_single_quotes)
{
	if (in_single_quotes)
		return (0);
	return (c == '$');
}

static char	*append_string_before_variable(char *result, char *str, int start, int i)
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

static char	*expand_variable_at_position(char *result, char *str, int *i)
{
	char	*var_name;
	char	*var_value;
	char	*temp;

	var_name = extract_var_name(str, i);
	if (!var_name)
		return (result);
	var_value = get_variable_value(var_name);
	if (var_value)
	{
		temp = ft_strjoin(result, var_value);
		if (!temp)
		{
			free(var_value);
			return (result);
		}
		free(result);
		free(var_value);
		result = temp;
	}
	free(var_name);
	return (result);
}

char	*expand_string(char *str, int in_double_quotes)
{
	char	*result;
	int		i;
	int		in_single_quotes;
	int		start;

	if (!str)
		return (NULL);
	if (ft_strchr(str, '$') == NULL)
		return (ft_strdup(str));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	in_single_quotes = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			i++;
		}
		else if (str[i] == '$' && should_expand_in_quotes(str[i], in_single_quotes))
		{
			result = append_string_before_variable(result, str, start, i);
			result = expand_variable_at_position(result, str, &i);
			start = i;
		}
		else
			i++;
	}
	result = append_string_before_variable(result, str, start, i);
	return (result);
}

static void	expand_word_list(t_word_list *words)
{
	char	*expanded;

	while (words)
	{
		if (words->word && words->word->word)
		{
			expanded = expand_string(words->word->word, 0);
			if (expanded)
			{
				free(words->word->word);
				words->word->word = expanded;
			}
		}
		words = words->next;
	}
}

static void	expand_redirects(t_redirect *redirects)
{
	char	*expanded;

	while (redirects)
	{
		if (redirects->redirectee.filename
			&& redirects->redirectee.filename->word)
		{
			expanded = expand_string(redirects->redirectee.filename->word, 0);
			if (expanded)
			{
				free(redirects->redirectee.filename->word);
				redirects->redirectee.filename->word = expanded;
			}
		}
		redirects = redirects->next;
	}
}

void	expand_variables(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == cm_simple && cmd->Simple)
	{
		expand_word_list(cmd->Simple->words);
		expand_redirects(cmd->Simple->redirects);
	}
	else if (cmd->type == cm_connection && cmd->Connection)
	{
		expand_variables(cmd->Connection->first);
		expand_variables(cmd->Connection->second);
	}
}