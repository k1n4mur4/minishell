/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 20:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_CMD_H
# define MAKE_CMD_H

# include "command.h"
# include "libft.h"

/* Word creation functions */
t_word_desc	*alloc_word_desc(void);
t_word_desc	*make_bare_word(const char *string);
t_word_desc	*make_word(const char *string);
t_word_desc	*make_word_flags(t_word_desc *w, const char *string);
t_word_desc	*make_word_from_token(int token);

/* Word list functions */
t_word_list	*make_word_list(t_word_desc *word, t_word_list *wlink);

/* Command creation functions */
t_command	*make_command(t_command_type type, t_simple_com *pointer);
t_command	*make_simple_command(t_element element, t_command *command,
				int line);
t_command	*make_bare_simple_command(int line);
t_command	*command_connect(t_command *com1, t_command *com2, int connector);
t_command	*clean_simple_command(t_command *command);

/* Redirection functions */
t_redirect	*make_redirection(t_redirectee source, t_instruction instruction,
				t_redirectee dest_and_filename, int flags);

/* Memory management */
void		dispose_word(t_word_desc *w);
void		dispose_words(t_word_list *list);

#endif