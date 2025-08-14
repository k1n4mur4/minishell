/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:30:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 20:30:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static int	process_redirect_type(char **input, t_token **token)
{
	if (**input == '<' && *(*input + 1) == '<')
	{
		*input += 2;
		*token = create_token(TOKEN_HEREDOC, "<<");
	}
	else if (**input == '>' && *(*input + 1) == '>')
	{
		*input += 2;
		*token = create_token(TOKEN_APPEND, ">>");
	}
	else if (**input == '<')
	{
		(*input)++;
		*token = create_token(TOKEN_REDIRECT_IN, "<");
	}
	else if (**input == '>')
	{
		(*input)++;
		*token = create_token(TOKEN_REDIRECT_OUT, ">");
	}
	else
		return (0);
	return (1);
}

int	handle_redirect(char **input, t_token **tokens)
{
	t_token	*token;

	if (!process_redirect_type(input, &token))
		return (0);
	if (!token)
		return (-1);
	add_token_to_list(tokens, token);
	return (1);
}

int	handle_pipe(char **input, t_token **tokens)
{
	t_token	*token;

	if (**input == '|')
	{
		token = create_token(TOKEN_PIPE, "|");
		if (!token)
			return (-1);
		add_token_to_list(tokens, token);
		(*input)++;
		return (1);
	}
	return (0);
}

static void	setup_token_segments(t_token *token, t_segment_info *seg_info)
{
	if (seg_info && seg_info->count > 0)
	{
		token->segments = malloc(sizeof(t_quote_segment) * seg_info->count);
		if (token->segments)
		{
			ft_memcpy(token->segments, seg_info->segments,
				sizeof(t_quote_segment) * seg_info->count);
			token->segment_count = seg_info->count;
		}
	}
}

int	handle_word(char **input, t_token **tokens)
{
	char			*word;
	t_token			*token;
	t_quote_type	quote_type;
	t_segment_info	*seg_info;

	word = extract_word_with_segments(input, &quote_type, &seg_info);
	if (!word)
		return (-1);
	if (ft_strlen(word) == 0 && quote_type == QUOTE_NONE)
		return (free(word), free_segment_info(seg_info), 0);
	token = create_token(TOKEN_WORD, word);
	free(word);
	if (!token)
		return (free_segment_info(seg_info), -1);
	token->quote_type = quote_type;
	setup_token_segments(token, seg_info);
	free_segment_info(seg_info);
	add_token_to_list(tokens, token);
	return (1);
}
