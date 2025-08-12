/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 23:34:39 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 21:30:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*find_command_path(char *command)
{
	t_var	*path_var;
	char	**paths;
	char	*result;

	if (!command)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	path_var = find_variable("PATH");
	if (!path_var || !path_var->value)
		return (ft_strdup(command));
	paths = ft_split(path_var->value, ':');
	if (!paths)
		return (ft_strdup(command));
	result = search_in_paths(paths, command);
	free_string_array(paths);
	return (result);
}

char	**build_argv_array(t_word_list *words)
{
	char	**argv;
	int		count;
	int		fail_index;

	count = count_word_list(words);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	fail_index = fill_argv_array(argv, words, count);
	if (fail_index >= 0)
	{
		free_partial_argv(argv, fail_index);
		return (NULL);
	}
	argv[count] = NULL;
	return (argv);
}

char	**build_envp_array(void)
{
	char	**envp;
	int		count;
	int		result;

	count = count_variables();
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	result = fill_envp_array(envp, ft_var(NULL, GET), count);
	if (result < 0)
	{
		free_envp_array(envp);
		return (NULL);
	}
	envp[result] = NULL;
	return (envp);
}

void	execute_child_process(char *path, char **argv, char **envp)
{
	if (execve(path, argv, envp) == -1)
	{
		perror("minishell");
		exit(EXECUTION_FAILURE);
	}
}

int	wait_for_process(pid_t pid)
{
	int	status;

	if (pid == -1)
		return (1);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	handle_process_signals(status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
