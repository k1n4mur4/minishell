/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:35:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 05:35:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
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

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

static void	add_token_to_list(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	skip_spaces(char **input)
{
	int	count;

	count = 0;
	while (**input && is_whitespace(**input))
	{
		(*input)++;
		count++;
	}
	return (count);
}

static int	find_closing_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		return (i);
	return (-1);
}

static char	*extract_quoted_content(char **input)
{
	char	quote_char;
	int		quote_end;
	char	*content;
	int		content_len;

	quote_char = **input;
	quote_end = find_closing_quote(*input, quote_char);
	if (quote_end == -1)
		return (NULL);
	content_len = quote_end + 1;
	content = (char *)malloc(content_len + 1);
	if (!content)
		return (NULL);
	ft_strlcpy(content, *input, content_len + 1);
	*input += content_len;
	return (content);
}

static char	*extract_regular_word(char **input)
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

static char	*process_word_part(char **input, char *result)
{
	char	*part;
	char	*temp;

	if (**input == '\'' || **input == '"')
	{
		part = extract_quoted_content(input);
		if (!part)
		{
			ft_dprintf(STDERR_FILENO, "minishell: syntax error: unclosed quote\n");
			return (NULL);
		}
	}
	else
		part = extract_regular_word(input);
	if (!part)
		return (NULL);
	temp = ft_strjoin(result, part);
	free(part);
	return (temp);
}

static char	*extract_word(char **input)
{
	char	*result;
	char	*temp;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (**input && !is_whitespace(**input) && !is_metachar(**input))
	{
		temp = process_word_part(input, result);
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

static int	handle_redirect(char **input, t_token **tokens)
{
	t_token	*token;

	if (**input == '<' && *(*input + 1) == '<')
	{
		token = create_token(TOKEN_HEREDOC, "<<");
		*input += 2;
	}
	else if (**input == '>' && *(*input + 1) == '>')
	{
		token = create_token(TOKEN_APPEND, ">>");
		*input += 2;
	}
	else if (**input == '<')
	{
		token = create_token(TOKEN_REDIRECT_IN, "<");
		(*input)++;
	}
	else if (**input == '>')
	{
		token = create_token(TOKEN_REDIRECT_OUT, ">");
		(*input)++;
	}
	else
		return (0);
	if (!token)
		return (-1);
	add_token_to_list(tokens, token);
	return (1);
}

static int	handle_pipe(char **input, t_token **tokens)
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

static int	handle_word(char **input, t_token **tokens)
{
	char	*word;
	t_token	*token;

	word = extract_word(input);
	if (!word)
		return (-1);
	if (ft_strlen(word) == 0)
	{
		free(word);
		return (0);
	}
	token = create_token(TOKEN_WORD, word);
	free(word);
	if (!token)
		return (-1);
	add_token_to_list(tokens, token);
	return (1);
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
		if (is_metachar(*input))
		{
			if (*input == '|')
				result = handle_pipe(&input, &tokens);
			else
				result = handle_redirect(&input, &tokens);
		}
		else
			result = handle_word(&input, &tokens);
		if (result == -1)
		{
			free_tokens(tokens);
			return (NULL);
		}
	}
	return (tokens);
}

void	print_tokens(t_token *tokens)
{
	const char	*type_names[] = {
		"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT", "HEREDOC", "APPEND", "EOF"
	};

	printf("=== TOKENS ===\n");
	while (tokens)
	{
		printf("Type: %-12s Value: '%s'\n",
			type_names[tokens->type], tokens->value ? tokens->value : "(null)");
		tokens = tokens->next;
	}
	printf("==============\n");
}