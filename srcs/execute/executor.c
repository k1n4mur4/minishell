/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:20:21 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/13 01:21:05 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "shell.h"
#include "variables.h"
#include "sig.h"
#include <sys/stat.h>
#include <signal.h>
#include <readline/readline.h>

int	execute_command(t_command *cmd)
{
	int	exit_status;

	if (!cmd)
		return (EXECUTION_FAILURE);
	if (cmd->type == cm_simple)
		exit_status = execute_simple_command(cmd->simple);
	else if (cmd->type == cm_connection)
		exit_status = execute_connection(cmd->connection);
	else
		exit_status = EXECUTION_FAILURE;
	exit_value(exit_status, SET);
	return (exit_status);
}

static pid_t	setup_left_pipe_process(t_connection *conn, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		reset_signals();
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(execute_command(conn->first));
	}
	else if (pid < 0)
	{
		perror("minishell");
		close(pipefd[0]);
		close(pipefd[1]);
		setup_signals();
	}
	return (pid);
}

static pid_t	setup_right_pipe_process(t_connection *conn, int *pipefd,
							pid_t left_pid)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		reset_signals();
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(execute_command(conn->second));
	}
	else if (pid < 0)
	{
		perror("minishell");
		close(pipefd[0]);
		close(pipefd[1]);
		kill(left_pid, SIGTERM);
		setup_signals();
	}
	return (pid);
}

static int	finalize_pipeline(pid_t left_pid, pid_t right_pid, int *pipefd)
{
	int	left_status;
	int	right_status;

	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left_pid, &left_status, 0);
	waitpid(right_pid, &right_status, 0);
	setup_signals();
	if (WIFSIGNALED(right_status) && WTERMSIG(right_status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (WIFSIGNALED(right_status) && WTERMSIG(right_status) == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (WIFEXITED(right_status))
		return (WEXITSTATUS(right_status));
	else if (WIFSIGNALED(right_status))
		return (128 + WTERMSIG(right_status));
	return (EXECUTION_FAILURE);
}

int	execute_pipeline_connection(t_connection *conn)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipefd) == -1)
	{
		perror("minishell");
		return (EXECUTION_FAILURE);
	}
	setup_exec_signals();
	left_pid = setup_left_pipe_process(conn, pipefd);
	if (left_pid < 0)
		return (EXECUTION_FAILURE);
	right_pid = setup_right_pipe_process(conn, pipefd, left_pid);
	if (right_pid < 0)
		return (EXECUTION_FAILURE);
	return (finalize_pipeline(left_pid, right_pid, pipefd));
}
