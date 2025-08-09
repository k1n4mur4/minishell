/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:44:12 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 05:44:13 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "variables.h"
#include "shell.h"

int	validate_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export_var(const char *name, const char *value)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd((char *)name, STDOUT_FILENO);
	if (value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd((char *)value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	print_sorted_env(void)
{
	t_var	*current;

	current = ft_var(NULL, GET);
	while (current)
	{
		print_export_var(current->name, current->value);
		current = current->next;
	}
}

static int	export_variable(const char *arg)
{
	char	*equal_sign;
	char	*name;
	char	*value;
	t_var	*var;

	if (!validate_identifier(arg))
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier\n", arg);
		return (EXECUTION_FAILURE);
	}
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		name = ft_strdup(arg);
		value = NULL;
	}
	else
	{
		name = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
	}
	if (!name || (equal_sign && !value))
	{
		free(name);
		free(value);
		return (EXECUTION_FAILURE);
	}
	var = find_variable(name);
	if (var)
	{
		if (value)
			update_var_value(var, value);
	}
	else
	{
		var = make_var(name, value);
		if (var)
			make_varlist(var);
	}
	free(name);
	free(value);
	return (var ? EXECUTION_SUCCESS : EXECUTION_FAILURE);
}

int	builtin_export(t_word_list *args)
{
	t_word_list	*current;
	int			exit_status;

	if (!args)
		return (EXECUTION_FAILURE);
	if (count_args(args) == 1)
	{
		print_sorted_env();
		return (EXECUTION_SUCCESS);
	}
	exit_status = EXECUTION_SUCCESS;
	current = args->next;
	while (current)
	{
		if (current->word && current->word->word)
		{
			if (export_variable(current->word->word) != EXECUTION_SUCCESS)
				exit_status = EXECUTION_FAILURE;
		}
		current = current->next;
	}
	return (exit_status);
}