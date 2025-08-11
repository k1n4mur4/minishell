/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:06:03 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 05:54:23 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "config.h"
# include "variables.h"
# include "exit_shell.h"
# include "sig.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "builtins.h"
# include "make_cmd.h"

# include "libft.h"

# define EXECUTION_FAILURE	1
# define EXECUTION_SUCCESS	0

// shell.c
int			main(int argc, char **argv, char **envp);

// shell_utils.c
char		*get_prompt(void);
void		shell_initialize(void);

// shell_command.c
void		process_command_line(char *line);

#endif