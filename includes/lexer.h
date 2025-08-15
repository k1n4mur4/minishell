/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:30:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 05:30:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stdio.h>

typedef struct s_quote_segment	t_quote_segment;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF
}	t_token_type;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	QUOTE_LOCALE
}	t_quote_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	t_quote_type		quote_type;
	t_quote_segment		*segments;
	int					segment_count;
	struct s_token		*next;
}	t_token;

t_token	*tokenize_input(char *input);
void	free_tokens(t_token *tokens);
t_token	*create_token(t_token_type type, char *value);

#endif