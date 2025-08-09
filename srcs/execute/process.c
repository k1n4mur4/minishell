/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:25:12 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 05:25:13 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "variables.h"
#include "shell.h"
#include <sys/stat.h>

char	*find_command_path(char *command)
{
	t_var	*path_var;
	char	**paths;
	char	*full_path;
	int		i;

	if (!command)
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	path_var = find_variable("PATH");
	if (!path_var || !path_var->value)
		return (NULL);
	paths = ft_split(path_var->value, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = build_path(paths[i], command);
		if (full_path && access(full_path, F_OK | X_OK) == 0)
		{
			free_string_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_string_array(paths);
	return (NULL);
}

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

char	**build_argv_array(t_word_list *words)
{
	t_word_list	*current;
	char		**argv;
	int			count;
	int			i;

	count = count_word_list(words);
	if (count == 0)
		return (NULL);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	current = words;
	i = 0;
	while (current && i < count)
	{
		if (current->word && current->word->word)
		{
			argv[i] = ft_strdup(current->word->word);
			if (!argv[i])
			{
				free_argv_array(argv);
				return (NULL);
			}
			i++;
		}
		current = current->next;
	}
	argv[i] = NULL;
	return (argv);
}

char	**build_envp_array(void)
{
	t_var	*current;
	char	**envp;
	int		count;
	int		i;

	count = count_variables();
	if (count == 0)
		return (NULL);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	current = ft_var(NULL, GET);
	i = 0;
	while (current && i < count)
	{
		envp[i] = build_env_string(current->name, current->value);
		if (!envp[i])
		{
			free_envp_array(envp);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	*build_env_string(char *name, char *value)
{
	char	*env_str;
	int		name_len;
	int		value_len;

	if (!name)
		return (NULL);
	name_len = ft_strlen(name);
	value_len = value ? ft_strlen(value) : 0;
	env_str = malloc(name_len + value_len + 2);
	if (!env_str)
		return (NULL);
	ft_strlcpy(env_str, name, name_len + value_len + 2);
	ft_strlcat(env_str, "=", name_len + value_len + 2);
	if (value)
		ft_strlcat(env_str, value, name_len + value_len + 2);
	return (env_str);
}

int	wait_for_process(pid_t pid)
{
	int	status;
	int	exit_code;

	if (waitpid(pid, &status, 0) == -1)
		return (EXECUTION_FAILURE);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	else
		exit_code = EXECUTION_FAILURE;
	return (exit_code);
}

void	init_exec_context(t_exec_context *ctx)
{
	if (!ctx)
		return ;
	ctx->stdin_backup = -1;
	ctx->stdout_backup = -1;
	ctx->stderr_backup = -1;
	ctx->pipe_read = -1;
	ctx->pipe_write = -1;
}

void	cleanup_exec_context(t_exec_context *ctx)
{
	if (!ctx)
		return ;
	if (ctx->pipe_read != -1)
		close(ctx->pipe_read);
	if (ctx->pipe_write != -1)
		close(ctx->pipe_write);
}