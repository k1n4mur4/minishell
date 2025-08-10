/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:42:19 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 04:09:14 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "variables.h"
#include "shell.h"

static void	set_pwd_var(char *new_pwd)
{
	t_var	*pwd_var;

	pwd_var = find_variable("PWD");
	if (!pwd_var)
	{
		pwd_var = make_var("PWD", new_pwd);
		if (pwd_var)
			make_varlist(pwd_var);
	}
	else
		update_var_value(pwd_var, new_pwd);
}

static void	set_oldpwd_var(char *old_pwd)
{
	t_var	*oldpwd_var;

	oldpwd_var = find_variable("OLDPWD");
	if (!oldpwd_var)
	{
		oldpwd_var = make_var("OLDPWD", old_pwd);
		if (oldpwd_var)
			make_varlist(oldpwd_var);
	}
	else
		update_var_value(oldpwd_var, old_pwd);
}

static int	update_pwd_variables(char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (EXECUTION_FAILURE);
	set_pwd_var(new_pwd);
	set_oldpwd_var(old_pwd);
	free(new_pwd);
	return (EXECUTION_SUCCESS);
}

static char	*get_target_directory(t_word_list *args)
{
	char	*target_dir;
	int		argc;

	argc = count_args(args);
	if (argc == 1)
	{
		target_dir = get_home_directory();
		if (!target_dir)
			ft_dprintf(STDERR_FILENO, "minishell: cd: HOME not set\n");
		return (target_dir);
	}
	else if (argc == 2)
		return (args->next->word->word);
	else
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		return (NULL);
	}
}

int	builtin_cd(t_word_list *args)
{
	char	*target_dir;
	char	*old_pwd;

	if (!args)
		return (EXECUTION_FAILURE);
	target_dir = get_target_directory(args);
	if (!target_dir)
		return (EXECUTION_FAILURE);
	old_pwd = getcwd(NULL, 0);
	if (chdir(target_dir) != 0)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (EXECUTION_FAILURE);
	}
	update_pwd_variables(old_pwd);
	free(old_pwd);
	return (EXECUTION_SUCCESS);
}
