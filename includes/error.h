/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/12 00:25:38 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdarg.h>
# include "config.h"
# include "exit_value.h"
# include "libft.h"

/* Syntax error messages */
# define ERR_SYNTAX_NEWLINE "syntax error near unexpected token `newline'"
# define ERR_SYNTAX_TOKEN "syntax error near unexpected token `%s'\n"
# define ERR_Q "syntax error: unexpected EOF while looking for matching `%c'\n"

/* File operation error messages */
# define ERR_NO_SUCH_FILE "%s: No such file or directory"
# define ERR_PERMISSION_DENIED "%s: Permission denied"
# define ERR_IS_DIRECTORY "%s: Is a directory"

/* Command error messages */
# define ERR_COMMAND_NOT_FOUND "%s: command not found"

/* Memory error messages */
# define ERR_MALLOC_FAILED "malloc failed"

/* Pipe error messages */
# define ERR_PIPE_FAILED "pipe failed"

/* Fork error messages */
# define ERR_FORK_FAILED "fork failed"

/* Error printing functions */
void	programming_error(const char *format, ...);
void	parser_error(char *iname, const char *format, ...);

#endif