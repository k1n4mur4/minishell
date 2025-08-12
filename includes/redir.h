/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:35:10 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/13 03:05:02 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "command.h"
# include "executor.h"
# include "libft.h"
# include "sig.h"
# include "expander.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>

# define HEREDOC_PIPESIZE 4096
# define TEMP_HERE_DOC "/tmp/tempXXXXXX"

typedef struct s_exec_context	t_exec_context;

int				setup_redirections(t_redirect *redirects, t_exec_context *ctx);
int				restore_redirections(t_exec_context *ctx);
int				setup_single_redirect(t_redirect *redir);
int				handle_input_redirect(char *filename);
int				handle_output_redirect(char *filename, int append);
int				redirect_heredoc(char *delimiter);

int				is_output_redirect(t_redirect *redirect);
t_redirect		*find_last_input_redirect(t_redirect *redirects);
int				open_output_file(char *filename, int append);
t_redirect		*find_first_output_redirect(t_redirect *redirects);

int				process_all_redirections(t_redirect *redirects,
					t_exec_context *ctx);

#endif