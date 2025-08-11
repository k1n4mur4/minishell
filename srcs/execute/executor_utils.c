/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:25:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 04:25:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "shell.h"
#include "sig.h"

int	execute_simple_command(t_simple_com *cmd)
{
	t_exec_context	ctx;
	char			*command_name;
	int				exit_status;

	if (!cmd || !cmd->words)
		return (EXECUTION_SUCCESS);
	command_name = cmd->words->word->word;
	if (!command_name)
		return (EXECUTION_SUCCESS);
	init_exec_context(&ctx);
	if (setup_redirections(cmd->redirects, &ctx) != EXECUTION_SUCCESS)
	{
		cleanup_exec_context(&ctx);
		return (EXECUTION_FAILURE);
	}
	if (is_builtin(command_name))
		exit_status = execute_builtin(cmd);
	else
		exit_status = execute_external_command(cmd);
	restore_redirections(&ctx);
	cleanup_exec_context(&ctx);
	return (exit_status);
}

static int	prepare_external_command(t_simple_com *cmd, char **command_path,
			char ***argv, char ***envp)
{
	*command_path = find_command_path(cmd->words->word->word);
	if (!*command_path)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n",
			cmd->words->word->word);
		return (CMD_NOT_FOUND);
	}
	*argv = build_argv_array(cmd->words);
	*envp = build_envp_array();
	if (!*argv || !*envp)
	{
		free(*command_path);
		free_argv_array(*argv);
		free_envp_array(*envp);
		return (EXECUTION_FAILURE);
	}
	return (EXECUTION_SUCCESS);
}

static int	handle_fork_and_exec(char *command_path, char **argv, char **envp)
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

int	execute_external_command(t_simple_com *cmd)
{
	char	*command_path;
	char	**argv;
	char	**envp;
	int		exit_status;

	if (prepare_external_command(cmd, &command_path, &argv, &envp))
		return (EXECUTION_FAILURE);
	exit_status = handle_fork_and_exec(command_path, argv, envp);
	free(command_path);
	free_argv_array(argv);
	free_envp_array(envp);
	return (exit_status);
}

int	execute_connection(t_connection *conn)
{
	int	exit_status;

	if (!conn)
		return (EXECUTION_FAILURE);
	if (conn->connector == '|')
		exit_status = execute_pipeline_connection(conn);
	else
		exit_status = EXECUTION_FAILURE;
	return (exit_status);
}
