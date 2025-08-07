/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:49:39 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/07 00:20:43 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	main(int argc, char **argv, char **env)
{
	if (argc > 1)
	{
		if (ft_strcmp(argv[1], "--version") == 0)
		{
			show_shell_version(1);
			exit (EXECUTION_SUCCESS);
		}
		ft_dprintf(STDERR_FILENO,
			"%s: %s: No such file or directory\n",
			PROGRAM, argv[1]);
		return (127);
	}
	initialize_shell_variables(env);
	run_all_tests();
	// shell_initialize();
	// if (isatty(STDIN_FILENO))
	// 	reader_loop();
	// else
	// 	execute_stdin_commands();
	exit_shell();
	return (exit_value(EXECUTION_SUCCESS, GET));
}
