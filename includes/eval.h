/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:55:01 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/13 03:20:30 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_H
# define EVAL_H

# include "libft.h"
# include "sig.h"
# include "exit_shell.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "make_cmd.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

# define EXECUTION_SUCCESS	0
# define EXECUTION_FAILURE	1

char		*get_prompt(void);
void		process_command_line(char *line);

int			reader_loop(void);
char		*read_input_line(void);

#endif