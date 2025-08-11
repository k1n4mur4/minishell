/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:30:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 20:30:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

int	find_closing_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		return (i);
	return (-1);
}

char	*extract_quoted_content(char **input, t_quote_type *quote_type)
{
	char	quote_char;
	int		quote_end;
	char	*content;
	int		content_len;

	quote_char = **input;
	if (quote_char == '\'')
		*quote_type = QUOTE_SINGLE;
	else
		*quote_type = QUOTE_DOUBLE;
	quote_end = find_closing_quote(*input, quote_char);
	if (quote_end == -1)
		return (NULL);
	content_len = quote_end - 1;
	if (content_len < 0)
		content_len = 0;
	content = (char *)malloc(content_len + 1);
	if (!content)
		return (NULL);
	if (content_len > 0)
		ft_strlcpy(content, *input + 1, content_len + 1);
	else
		content[0] = '\0';
	*input += quote_end + 1;
	return (content);
}

char	*extract_regular_word(char **input)
{
	char	*start;
	int		len;
	char	*word;

	start = *input;
	len = 0;
	while (**input && !is_whitespace(**input) && !is_metachar(**input)
		&& **input != '\'' && **input != '"')
	{
		(*input)++;
		len++;
	}
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}

static char	*handle_locale_or_quote(char **input, t_quote_type *q_type)
{
	char			*part;
	t_quote_type	current_quote;

	if (**input == '$' && *(*input + 1) == '"')
		part = extract_locale_string(input, &current_quote);
	else
		part = extract_quoted_content(input, &current_quote);
	if (!part)
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: syntax error: unclosed quote\n");
		return (NULL);
	}
	if (*q_type == QUOTE_NONE)
		*q_type = current_quote;
	return (part);
}

char	*process_word_part(char **input, char *result, t_quote_type *q_type)
{
	char	*part;
	char	*temp;

	if (**input == '$' && *(*input + 1) == '"')
		part = handle_locale_or_quote(input, q_type);
	else if (**input == '\'' || **input == '"')
		part = handle_locale_or_quote(input, q_type);
	else
		part = extract_regular_word(input);
	if (!part)
		return (NULL);
	temp = ft_strjoin(result, part);
	free(part);
	return (temp);
}
