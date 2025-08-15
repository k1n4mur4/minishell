/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_segments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:10:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 22:10:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"

static char	*expand_no_segments(t_word_desc *word_desc)
{
	if (word_desc->quote_type == QUOTE_SINGLE)
		return (ft_strdup(word_desc->word));
	else if (word_desc->quote_type == QUOTE_LOCALE)
		return (ft_strdup(word_desc->word));
	else if (word_desc->quote_type == QUOTE_DOUBLE)
		return (expand_string(word_desc->word, 1));
	else
		return (expand_string(word_desc->word, 0));
}

static char	*expand_segment_by_type(char *segment_str, t_quote_type type)
{
	if (type == QUOTE_SINGLE || type == QUOTE_LOCALE)
		return (ft_strdup(segment_str));
	else if (type == QUOTE_DOUBLE)
		return (expand_string(segment_str, 1));
	else
		return (expand_string(segment_str, 0));
}

static char	*process_single_segment(t_word_desc *word_desc, int i)
{
	char	*segment_str;
	char	*temp;

	segment_str = ft_substr(word_desc->word,
			word_desc->segments[i].start, word_desc->segments[i].length);
	if (!segment_str)
		return (NULL);
	temp = expand_segment_by_type(segment_str,
			word_desc->segments[i].quote_type);
	free(segment_str);
	return (temp);
}

static char	*join_segments(char *result, char *temp)
{
	char	*new_result;

	new_result = ft_strjoin(result, temp);
	free(result);
	free(temp);
	return (new_result);
}

char	*expand_word_with_segments(t_word_desc *word_desc)
{
	char	*result;
	char	*temp;
	int		i;

	if (!word_desc->segments || word_desc->segment_count == 0)
		return (expand_no_segments(word_desc));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = -1;
	while (++i < word_desc->segment_count)
	{
		temp = process_single_segment(word_desc, i);
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		result = join_segments(result, temp);
		if (!result)
			return (NULL);
	}
	return (result);
}
