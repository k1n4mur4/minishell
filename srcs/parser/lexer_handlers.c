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

int	handle_word(char **input, t_token **tokens)
{
	char			*word;
	t_token			*token;
	t_quote_type	quote_type;

	word = extract_word(input, &quote_type);
	if (!word)
		return (-1);
	if (ft_strlen(word) == 0 && quote_type == QUOTE_NONE)
	{
		free(word);
		return (0);
	}
	token = create_token(TOKEN_WORD, word);
	free(word);
	if (!token)
		return (-1);
	token->quote_type = quote_type;
	add_token_to_list(tokens, token);
	return (1);
}
