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
# include "command.h"
# include "shell.h"
# include "libft.h"
# include <stdlib.h>

typedef struct s_segment_info
{
	t_quote_segment	*segments;
	int				count;
	int				capacity;
}				t_segment_info;

/* Core functions - lexer_core.c */
void			add_token_to_list(t_token **head, t_token *new_token);
int				skip_spaces(char **input);

/* Extract functions - lexer_extract.c */
char			*extract_quoted_content(char **input, t_quote_type *quote_type);
char			*extract_regular_word(char **input);
char			*process_word_part(char **input, char *result,
					t_quote_type *q_type);
int				find_closing_quote(char *str, char quote);

/* Locale functions - lexer_locale.c */
char			*extract_locale_string(char **input, t_quote_type *quote_type);
char			*extract_word(char **input, t_quote_type *quote_type);
char			*extract_word_with_segments(char **input,
					t_quote_type *quote_type, t_segment_info **seg_info_ptr);

/* Handler functions - lexer_handlers.c */
int				handle_word(char **input, t_token **tokens);
int				handle_redirect(char **input, t_token **tokens);
int				handle_pipe(char **input, t_token **tokens);
int				is_whitespace(char c);
int				is_metachar(char c);

t_segment_info	*init_segment_info(void);
int				add_segment(t_segment_info *info, int start, int length,
					t_quote_type quote_type);
void			free_segment_info(t_segment_info *info);
char			*process_word_part_with_segments(char **input, char *result,
					t_quote_type *q_type, t_segment_info *seg_info);
char			*extract_and_add_segment(char **input, t_segment_info *seg_info,
					int part_start, t_quote_type *current_quote);
char			*handle_locale_or_quote(char **input, t_quote_type *q_type);

#endif