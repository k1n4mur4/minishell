/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/15 03:40:45 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"

char	*read_input_line(void)
{
	char	*prompt;
	char	*line;

	g_interrupt_state = 0;
	prompt = get_prompt();
	line = readline(prompt);
	if (!line)
		ft_printf("exit\n");
	return (line);
}

int	reader_loop(void)
{
	char	*line;

	setup_signals();
	while (1)
	{
		line = read_input_line();
		if (!line)
			break ;
		if (*line)
			add_history(line);
		process_command_line(line);
		free(line);
		if (exit_readline(0) == 1)
		{
			ft_printf("exit\n");
			break ;
		}
	}
	return (exit_value(EXECUTION_SUCCESS, GET));
}
