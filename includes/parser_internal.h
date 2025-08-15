/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 21:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "parser.h"
# include "command.h"
# include "lexer.h"
# include "shell.h"
# include "libft.h"

# define SYNTAX_ERROR 2

/* Core parsing functions - parser.c */
t_redirect	*create_redirect(t_token_type type, char *filename);

/* Helper functions - parser_helpers.c */
int			process_simple_tokens(t_simple_com *simple, t_token **tokens);
t_command	*create_simple_command(t_simple_com *simple);
void		cleanup_pipeline_error(t_command *left, t_command *right,
				t_connection *conn);

/* Utility functions - parser_utils.c */
void		handle_simple_command_word(t_simple_com *simple, t_token **tokens);
int			handle_simple_command_redirections(t_simple_com *simple,
				t_token **tokens);

/* Error handling functions */
int			report_syntax_error(t_token *token);
int			is_valid_redirect_syntax(t_token *current);
void		reset_syntax_error_flag(void);

#endif