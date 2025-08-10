/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:40:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 05:58:25 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef enum e_instruction
{
	r_output_direction,
	r_input_direction,
	r_inputa_direction,
	r_appending_to,
	r_reading_until,
	r_reading_string,
	r_duplicating_input,
	r_duplicating_output,
	r_deblank_reading_until,
	r_close_this,
	r_err_and_out,
	r_input_output,
	r_output_force,
	r_duplicating_input_word,
	r_duplicating_output_word,
	r_move_input,
	r_move_output,
	r_move_input_word,
	r_move_output_word,
	r_append_err_and_out
}	t_instruction;

typedef enum e_command_type
{
	cm_for,
	cm_case,
	cm_while,
	cm_if,
	cm_simple,
	cm_select,
	cm_connection,
	cm_function_def,
	cm_until,
	cm_group,
	cm_arith,
	cm_cond,
	cm_arith_for,
	cm_subshell,
	cm_coproc
}	t_command_type;

typedef struct s_word_desc
{
	char	*word;
	int		flags;
	int		quote_type;
}				t_word_desc;

typedef struct s_word_list
{
	struct s_word_list	*next;
	t_word_desc			*word;
}				t_word_list;

typedef struct s_redirectee
{
	int			dest;
	t_word_desc	*filename;
}				t_redirectee;

typedef struct s_redirect
{
	struct s_redirect	*next;
	t_redirectee		redirector;
	int					rflags;
	int					flags;
	t_instruction		instruction;
	t_redirectee		redirectee;
	char				*here_doc_eof;
}				t_redirect;

typedef struct s_element
{
	t_word_desc	*word;
	t_redirect	*redirect;
}				t_element;

typedef struct s_simple_com	t_simple_com;
typedef struct s_connection	t_connection;

typedef struct s_command
{
	t_command_type	type;
	int				flags;
	int				line;
	t_redirect		*redirect;
	t_connection	*connection;
	t_simple_com	*simple;
}				t_command;

typedef struct s_simple_com
{
	int				flags;
	int				line;
	t_word_list		*words;
	t_redirect		*redirects;
}				t_simple_com;

typedef struct s_connection
{
	int			ignore;
	t_command	*first;
	t_command	*second;
	int			connector;
}				t_connection;

#endif