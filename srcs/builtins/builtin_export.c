/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:44:12 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 04:09:43 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	validate_export_arg(const char *arg)
{
	if (!validate_identifier(arg))
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier\n", arg);
		return (EXECUTION_FAILURE);
	}
	return (EXECUTION_SUCCESS);
}

static int	parse_export_argument(const char *arg, char **name, char **value)
{
	char	*equal_sign;

	if (validate_export_arg(arg) == EXECUTION_FAILURE)
		return (EXECUTION_FAILURE);
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		*name = ft_strdup(arg);
		*value = NULL;
	}
	else
	{
		*name = ft_substr(arg, 0, equal_sign - arg);
		*value = ft_strdup(equal_sign + 1);
	}
	if (!*name || (equal_sign && !*value))
		return (EXECUTION_FAILURE);
	return (EXECUTION_SUCCESS);
}

static int	create_or_update_variable(char *name, char *value)
{
	t_var	*var;

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
	if (var)
		return (EXECUTION_SUCCESS);
	return (EXECUTION_FAILURE);
}

static int	export_variable(const char *arg)
{
	char	*name;
	char	*value;
	int		result;

	if (parse_export_argument(arg, &name, &value) == EXECUTION_FAILURE)
	{
		free(name);
		free(value);
		return (EXECUTION_FAILURE);
	}
	result = create_or_update_variable(name, value);
	free(name);
	free(value);
	return (result);
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
