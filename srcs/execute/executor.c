/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:20:21 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 05:20:22 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "shell.h"
#include "variables.h"
#include "sig.h"
#include <sys/stat.h>
#include <signal.h>

int	execute_command(t_command *cmd)
{
	int	exit_status;

	if (!cmd)
		return (EXECUTION_FAILURE);
	if (cmd->type == cm_simple)
		exit_status = execute_simple_command(cmd->Simple);
	else if (cmd->type == cm_connection)
		exit_status = execute_connection(cmd->Connection);
	else
		exit_status = EXECUTION_FAILURE;
	exit_value(exit_status, SET);
	return (exit_status);
}

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

int	execute_external_command(t_simple_com *cmd)
{
	char	*command_path;
	char	**argv;
	char	**envp;
	pid_t	pid;
	int		exit_status;

	command_path = find_command_path(cmd->words->word->word);
	if (!command_path)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n",
			cmd->words->word->word);
		return (CMD_NOT_FOUND);
	}
	argv = build_argv_array(cmd->words);
	envp = build_envp_array();
	if (!argv || !envp)
	{
		free(command_path);
		free_argv_array(argv);
		free_envp_array(envp);
		return (EXECUTION_FAILURE);
	}
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
	free(command_path);
	free_argv_array(argv);
	free_envp_array(envp);
	return (exit_status);
}

void	execute_child_process(char *path, char **argv, char **envp)
{
	if (execve(path, argv, envp) == -1)
	{
		perror("minishell");
		exit(EXECUTION_FAILURE);
	}
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

int	execute_pipeline_connection(t_connection *conn)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		left_status;
	int		right_status;

	if (pipe(pipefd) == -1)
	{
		perror("minishell");
		return (EXECUTION_FAILURE);
	}
	setup_exec_signals();
	left_pid = fork();
	if (left_pid == 0)
	{
		reset_signals();
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(execute_command(conn->first));
	}
	else if (left_pid < 0)
	{
		perror("minishell");
		close(pipefd[0]);
		close(pipefd[1]);
		setup_signals();
		return (EXECUTION_FAILURE);
	}
	right_pid = fork();
	if (right_pid == 0)
	{
		reset_signals();
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(execute_command(conn->second));
	}
	else if (right_pid < 0)
	{
		perror("minishell");
		close(pipefd[0]);
		close(pipefd[1]);
		kill(left_pid, SIGTERM);
		setup_signals();
		return (EXECUTION_FAILURE);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left_pid, &left_status, 0);
	waitpid(right_pid, &right_status, 0);
	setup_signals();
	if (WIFEXITED(right_status))
		return (WEXITSTATUS(right_status));
	else if (WIFSIGNALED(right_status))
		return (128 + WTERMSIG(right_status));
	return (EXECUTION_FAILURE);
}