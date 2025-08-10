/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:30:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 20:30:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->quote_type = QUOTE_NONE;
	if (value)
	{
		token->value = ft_strdup(value);
		if (!token->value)
		{
			free(token);
			return (NULL);
		}
	}
	else
		token->value = NULL;
	token->next = NULL;
	return (token);
}

static int	process_token(char **input, t_token **tokens)
{
	int	result;

	if (is_metachar(**input))
	{
		if (**input == '|')
			result = handle_pipe(input, tokens);
		else
			result = handle_redirect(input, tokens);
	}
	else
		result = handle_word(input, tokens);
	return (result);
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	int		result;

	if (!input)
		return (NULL);
	tokens = NULL;
	while (*input)
	{
		skip_spaces(&input);
		if (!*input)
			break ;
		result = process_token(&input, &tokens);
		if (result == -1)
		{
			free_tokens(tokens);
			return (NULL);
		}
	}
	return (tokens);
}
