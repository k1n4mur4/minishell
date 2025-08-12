/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:30:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 20:30:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include "lexer.h"
# include "shell.h"
# include "libft.h"
# include <stdlib.h>

/* Core functions - lexer_core.c */
void	add_token_to_list(t_token **head, t_token *new_token);
int		skip_spaces(char **input);

/* Extract functions - lexer_extract.c */
char	*extract_quoted_content(char **input, t_quote_type *quote_type);
char	*extract_regular_word(char **input);
char	*process_word_part(char **input, char *result, t_quote_type *q_type);
int		find_closing_quote(char *str, char quote);

/* Locale functions - lexer_locale.c */
char	*extract_locale_string(char **input, t_quote_type *quote_type);
char	*extract_word(char **input, t_quote_type *quote_type);

/* Handler functions - lexer_handlers.c */
int		handle_word(char **input, t_token **tokens);
int		handle_redirect(char **input, t_token **tokens);
int		handle_pipe(char **input, t_token **tokens);
int		is_whitespace(char c);
int		is_metachar(char c);

#endif