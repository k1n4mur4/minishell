/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 06:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 06:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "command.h"
# include "libft.h"

t_command	*parse_command_line(t_token *tokens);
t_command	*parse_simple_command(t_token **tokens);
t_command	*parse_pipeline(t_token **tokens);
t_redirect	*parse_redirections(t_token **tokens);

t_word_desc	*create_word(char *str);
t_word_list	*create_word_list(t_word_desc *word);
void		add_word_to_list(t_word_list **list, t_word_desc *word);

void		free_command(t_command *cmd);
void		free_word_list(t_word_list *list);
void		free_redirect(t_redirect *redir);
void		print_command(t_command *cmd);

#endif