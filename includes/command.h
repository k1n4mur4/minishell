#ifndef	COMMAND_H
# define	COMMAND_H

typedef enum	e_instruction
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

typedef enum	e_command_type
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

typedef struct	s_word_desc
{
	char *word;
	int flags;
}				t_word_desc;

typedef struct	s_word_list
{
	struct s_word_list	*next;
	t_word_desc			*word;
}				t_word_list;

typedef struct	s_redirectee
{
	int			dest;
	t_word_desc	*filename;
}				t_redirectee;

typedef struct	s_redirect
{
	struct s_redirect *next;	/* Next element, or NULL. */
	t_redirectee redirector;	/* Descriptor or varname to be redirected. */
	int rflags;			/* Private flags for this redirection */
	int flags;			/* Flag value for `open'. */
	t_instruction	instruction; /* What to do with the information. */
	t_redirectee redirectee;	/* File descriptor or filename */
	char *here_doc_eof;		/* The word that appeared in <<foo. */
}				t_redirect;

typedef struct	s_element
{
	t_word_desc	*word;
	t_redirect	*redirect;
}				t_element;

typedef struct	s_simple_com	t_simple_com;
typedef struct	s_connection	t_connection;

typedef struct	s_command
{
	t_command_type	type;	/* FOR CASE WHILE IF CONNECTION or SIMPLE. */
	int				flags;			/* Flags controlling execution environment. */
	int				line;			/* line number the command starts on */
	t_redirect		*redirect;		/* Special redirects for FOR CASE, etc. */
	t_connection	*Connection;
	t_simple_com	*Simple;
}				t_command;

typedef struct	s_simple_com
{
	int flags;			/* See description of CMD flags. */
	int line;			/* line number the command starts on */
	t_word_list *words;		/* The program name, the arguments, variable assignments, etc. */
	t_redirect *redirects;		/* Redirections to perform. */
}				t_simple_com;

typedef struct	s_connection
{
	int			ignore;			/* Unused; simplifies make_command (). */
	t_command	*first;		/* Pointer to the first command. */
	t_command	*second;		/* Pointer to the second command. */
	int			connector;		/* What separates this command from others. */
}				t_connection;

#endif