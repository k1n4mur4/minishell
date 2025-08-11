/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_locale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 18:30:26 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

char	*extract_locale_string(char **input, t_quote_type *quote_type)
{
	char	*content;
	int		quote_end;
	int		content_len;

	*quote_type = QUOTE_LOCALE;
	(*input)++;
	quote_end = find_closing_quote(*input, '"');
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

char	*extract_word(char **input, t_quote_type *quote_type)
{
	char	*result;
	char	*temp;

	*quote_type = QUOTE_NONE;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (**input && !is_whitespace(**input) && !is_metachar(**input))
	{
		temp = process_word_part(input, result, quote_type);
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		free(result);
		result = temp;
	}
	return (result);
}
