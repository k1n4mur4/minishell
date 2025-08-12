/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:49:10 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/13 01:15:40 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "shell.h"
#include "sig.h"

int	find_and_validate_command(t_simple_com *cmd, char **command_path)
{
	*command_path = find_command_path(cmd->words->word->word);
	if (!*command_path)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n",
			cmd->words->word->word);
		return (CMD_NOT_FOUND);
	}
	return (EXECUTION_SUCCESS);
}

int	build_command_arrays(t_simple_com *cmd, char ***argv, char ***envp)
{
	*argv = build_argv_array(cmd->words);
	*envp = build_envp_array();
	if (!*argv || !*envp)
	{
		free_argv_array(*argv);
		free_envp_array(*envp);
		return (EXECUTION_FAILURE);
	}
	return (EXECUTION_SUCCESS);
}

int	prepare_external_command(t_simple_com *cmd, char **command_path,
		char ***argv, char ***envp)
{
	if (find_and_validate_command(cmd, command_path) != EXECUTION_SUCCESS)
		return (CMD_NOT_FOUND);
	if (build_command_arrays(cmd, argv, envp) != EXECUTION_SUCCESS)
	{
		free(*command_path);
		return (EXECUTION_FAILURE);
	}
	return (EXECUTION_SUCCESS);
}

int	handle_fork_and_exec(char *command_path, char **argv, char **envp)
{
	pid_t	pid;
	int		exit_status;

	setup_exec_signals();
	pid = fork();
	if (pid == 0)
	{
		reset_signals();
		execute_child_process(command_path, argv, envp);
		exit(EXECUTION_FAILURE);
	}
	else if (pid > 0)
	{
		exit_status = wait_for_process(pid);
		setup_signals();
	}
	else
	{
		exit_status = EXECUTION_FAILURE;
		setup_signals();
	}
	return (exit_status);
}
