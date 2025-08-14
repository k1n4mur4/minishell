/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:30:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 20:30:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

t_segment_info	*init_segment_info(void)
{
	t_segment_info	*info;

	info = malloc(sizeof(t_segment_info));
	if (!info)
		return (NULL);
	info->segments = malloc(sizeof(t_quote_segment) * 4);
	if (!info->segments)
	{
		free(info);
		return (NULL);
	}
	info->count = 0;
	info->capacity = 4;
	return (info);
}

int	add_segment(t_segment_info *info, int start, int length,
		t_quote_type quote_type)
{
	t_quote_segment	*new_segments;

	if (!info)
		return (0);
	if (info->count >= info->capacity)
	{
		new_segments = malloc(sizeof(t_quote_segment) * info->capacity * 2);
		if (!new_segments)
			return (0);
		ft_memcpy(new_segments, info->segments,
			sizeof(t_quote_segment) * info->count);
		free(info->segments);
		info->segments = new_segments;
		info->capacity *= 2;
	}
	info->segments[info->count].start = start;
	info->segments[info->count].length = length;
	info->segments[info->count].quote_type = quote_type;
	info->count++;
	return (1);
}

void	free_segment_info(t_segment_info *info)
{
	if (info)
	{
		free(info->segments);
		free(info);
	}
}

char	*handle_locale_or_quote(char **input, t_quote_type *q_type)
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

char	*extract_and_add_segment(char **input, t_segment_info *seg_info,
		int part_start, t_quote_type *current_quote)
{
	char	*part;
	int		part_len;

	if (**input == '$' && *(*input + 1) == '"')
		part = handle_locale_or_quote(input, current_quote);
	else if (**input == '\'' || **input == '"')
		part = handle_locale_or_quote(input, current_quote);
	else
	{
		part = extract_regular_word(input);
		*current_quote = QUOTE_NONE;
	}
	if (part && seg_info)
	{
		part_len = ft_strlen(part);
		add_segment(seg_info, part_start, part_len, *current_quote);
	}
	return (part);
}
