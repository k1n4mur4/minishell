/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:41:07 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/15 03:40:14 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit_helper(t_word_list *args, int argc)
{
	if (argc == 1)
	{
		exit_value(EXECUTION_SUCCESS, SET);
		return (EXIT_SUCCESS);
	}
	else if (argc > 2)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	else if (!args->next->word || !is_numeric(args->next->word->word))
	{
		if (!args->next->word)
			ft_dprintf(STDERR_FILENO, EXIT_ERR, "");
		else
			ft_dprintf(STDERR_FILENO, EXIT_ERR, args->next->word->word);
		return (EXIT_FAILURE);
	}
	exit_value(ft_atoi(args->next->word->word) % 256, SET);
	return (EXIT_SUCCESS);
}

int	builtin_exit(t_word_list *args)
{
	int	exit_code;
	int	argc;
	int	ret;

	if (!args)
		exit_value(EXECUTION_SUCCESS, SET);
	else
	{
		argc = count_args(args);
		ret = builtin_exit_helper(args, argc);
		if (ret != EXIT_SUCCESS)
		{
			exit_value(ret, SET);
			return (EXECUTION_FAILURE);
		}
	}
	exit_readline(1);
	exit_code = exit_value(0, GET);
	return (exit_code % 256);
}
