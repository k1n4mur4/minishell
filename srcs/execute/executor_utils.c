/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:25:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 17:49:33 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	execute_redirections_only(t_simple_com *cmd)
{
	t_exec_context	ctx;
	int				exit_status;

	init_exec_context(&ctx);
	if (setup_redirections(cmd->redirects, &ctx) != EXECUTION_SUCCESS)
	{
		cleanup_exec_context(&ctx);
		return (EXECUTION_FAILURE);
	}
	exit_status = EXECUTION_SUCCESS;
	restore_redirections(&ctx);
	cleanup_exec_context(&ctx);
	return (exit_status);
}

static int	execute_command_with_context(t_simple_com *cmd, t_exec_context *ctx,
		char *command_name)
{
	int	exit_status;

	if (setup_redirections(cmd->redirects, ctx) != EXECUTION_SUCCESS)
	{
		cleanup_exec_context(ctx);
		return (EXECUTION_FAILURE);
	}
	if (is_builtin(command_name))
		exit_status = execute_builtin(cmd);
	else
		exit_status = execute_external_command(cmd);
	restore_redirections(ctx);
	cleanup_exec_context(ctx);
	return (exit_status);
}

int	execute_simple_command(t_simple_com *cmd)
{
	t_exec_context	ctx;
	char			*command_name;

	if (!cmd)
		return (EXECUTION_SUCCESS);
	if (!cmd->words)
	{
		if (cmd->redirects)
			return (execute_redirections_only(cmd));
		return (EXECUTION_SUCCESS);
	}
	command_name = cmd->words->word->word;
	if (!command_name)
		return (EXECUTION_SUCCESS);
	init_exec_context(&ctx);
	return (execute_command_with_context(cmd, &ctx, command_name));
}

int	execute_external_command(t_simple_com *cmd)
{
	char	*command_path;
	char	**argv;
	char	**envp;
	int		exit_status;
	int		result;

	result = prepare_external_command(cmd, &command_path, &argv, &envp);
	if (result != EXECUTION_SUCCESS)
		return (result);
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
