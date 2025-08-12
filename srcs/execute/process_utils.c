/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:30:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 21:30:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*build_path(char *dir, char *command)
{
	char	*path;
	int		dir_len;
	int		cmd_len;

	if (!dir || !command)
		return (NULL);
	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(command);
	path = malloc(dir_len + cmd_len + 2);
	if (!path)
		return (NULL);
	ft_strlcpy(path, dir, dir_len + cmd_len + 2);
	if (dir_len > 0 && path[dir_len - 1] != '/')
		ft_strlcat(path, "/", dir_len + cmd_len + 2);
	ft_strlcat(path, command, dir_len + cmd_len + 2);
	return (path);
}

char	*build_env_string(char *name, char *value)
{
	char	*env_str;
	int		name_len;
	int		value_len;

	if (!name)
		return (NULL);
	name_len = ft_strlen(name);
	if (value)
		value_len = ft_strlen(value);
	else
		value_len = 0;
	env_str = malloc(name_len + value_len + 2);
	if (!env_str)
		return (NULL);
	ft_strlcpy(env_str, name, name_len + value_len + 2);
	ft_strlcat(env_str, "=", name_len + value_len + 2);
	if (value)
		ft_strlcat(env_str, value, name_len + value_len + 2);
	return (env_str);
}

void	init_exec_context(t_exec_context *ctx)
{
	if (!ctx)
		return ;
	ctx->stdin_backup = -1;
	ctx->stdout_backup = -1;
	ctx->stderr_backup = -1;
}

void	handle_process_signals(int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	cleanup_exec_context(t_exec_context *ctx)
{
	if (!ctx)
		return ;
	if (ctx->stdin_backup != -1)
	{
		dup2(ctx->stdin_backup, STDIN_FILENO);
		close(ctx->stdin_backup);
	}
	if (ctx->stdout_backup != -1)
	{
		dup2(ctx->stdout_backup, STDOUT_FILENO);
		close(ctx->stdout_backup);
	}
	if (ctx->stderr_backup != -1)
	{
		dup2(ctx->stderr_backup, STDERR_FILENO);
		close(ctx->stderr_backup);
	}
}
