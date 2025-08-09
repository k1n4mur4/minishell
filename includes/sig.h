#ifndef	SIG_H
# define	SIG_H

#include <signal.h>
#include "libft.h"

extern volatile sig_atomic_t	g_interrupt_state;

void	setup_signals(void);
void	setup_exec_signals(void);
void	reset_signals(void);

#endif