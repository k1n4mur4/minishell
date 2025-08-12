/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:40:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 14:57:41 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <signal.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

extern volatile sig_atomic_t	g_interrupt_state;

void	interactive_sigint_handler(int sig);
void	heredoc_sigint_handler(int sig);
int		heredoc_event_hook(void);
void	setup_signals(void);
void	setup_exec_signals(void);
void	reset_signals(void);
void	setup_heredoc_signals(void);

#endif