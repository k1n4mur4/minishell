/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:10:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 22:10:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_INTERNAL_H
# define EXPANDER_INTERNAL_H

# include "expander.h"
# include "lexer.h"
# include "shell.h"
# include "libft.h"

/* Expansion utility functions - expander_utils.c */
char	*extract_var_name(char *str, int *i);
int		should_expand_in_quotes(char c, int in_single_quotes);
char	*append_string_before_variable(char *result, char *str, int start,
			int i);
char	*expand_variable_at_position(char *result, char *str, int *i);
void	expand_word_list(t_word_list *words);
void	expand_redirects(t_redirect *redirects);
void	handle_quote_character(int *in_single_quotes, int *i);
char	*handle_variable_expansion(char *result, char *str, int *start, int *i);
char	*process_expansion_loop(char *result, char *str, int in_double_quotes);
char	*handle_no_var_name(char *result, int *i);
char	*append_var_value(char *result, char *var_value);
char	*handle_special_variable(char *str, int *i);
char	*allocate_var_name(char *str, int start, int len);

/* Segment expansion functions - expander_segments.c */
char	*expand_word_with_segments(t_word_desc *word_desc);

#endif