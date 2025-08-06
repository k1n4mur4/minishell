/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:06:03 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/06 03:39:36 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SHELL_H
# define SHELL_H

#include "config.h"

#include "config.h"
#include "variables.h"
#include "exit_shell.h"

#include "libft.h"

#define EXECUTION_FAILURE	1
#define EXECUTION_SUCCESS	0

// shell.c
int	main(int argc, char **argv, char **envp);

#endif