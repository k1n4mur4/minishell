/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:10:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 22:10:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"
#include "lexer.h"

void	handle_quote_character(int *in_single_quotes, int *i)
{
	*in_single_quotes = !(*in_single_quotes);
	(*i)++;
}

char	*handle_variable_expansion(char *result, char *str, int *start, int *i)
{
	result = append_string_before_variable(result, str, *start, *i);
	result = expand_variable_at_position(result, str, i);
	*start = *i;
	return (result);
}

char	*process_expansion_loop(char *result, char *str, int in_double_quotes)
{
	int	i;
	int	in_single_quotes;
	int	start;

	i = 0;
	in_single_quotes = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
			handle_quote_character(&in_single_quotes, &i);
		else if (str[i] == '$'
			&& should_expand_in_quotes(str[i], in_single_quotes))
			result = handle_variable_expansion(result, str, &start, &i);
		else
			i++;
	}
	result = append_string_before_variable(result, str, start, i);
	return (result);
}

void	expand_word_list(t_word_list *words)
{
	char	*expanded;

	while (words)
	{
		if (words->word && words->word->word)
		{
			if (words->word->quote_type == QUOTE_SINGLE)
				expanded = ft_strdup(words->word->word);
			else if (words->word->quote_type == QUOTE_LOCALE)
				expanded = ft_strdup(words->word->word);
			else if (words->word->quote_type == QUOTE_DOUBLE)
				expanded = expand_string(words->word->word, 1);
			else
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

void	expand_redirects(t_redirect *redirects)
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
