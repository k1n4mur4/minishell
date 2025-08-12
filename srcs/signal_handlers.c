/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/13 01:27:14 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include <readline/readline.h>
#include <readline/history.h>

void	interactive_sigint_handler(int sig)
{
	(void)sig;
	g_interrupt_state = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
