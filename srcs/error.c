/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:14:09 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/12 00:20:18 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	programming_error(const char *format, ...)
{
	va_list	args;

	ft_dprintf(STDERR_FILENO, "%s: ", PROGRAM);
	va_start(args, format);
	ft_vdprintf(STDERR_FILENO, format, args);
	va_end(args);
	exit(1);
}

void	parser_error(char *iname, const char *format, ...)
{
	va_list	args;

	if (!iname)
		ft_dprintf(STDERR_FILENO, "%s: ", PROGRAM);
	else
		ft_dprintf(STDERR_FILENO, "%s: %s: ", PROGRAM, iname);
	va_start(args, format);
	ft_vdprintf(STDERR_FILENO, format, args);
	va_end(args);
	exit_value(2, SET);
}
