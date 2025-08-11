/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:41:07 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 04:08:40 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "shell.h"

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

int	builtin_exit(t_word_list *args)
{
	int	exit_code;
	int	argc;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!args)
		exit(EXECUTION_SUCCESS);
	argc = count_args(args);
	if (argc == 1)
		exit(exit_value(EXECUTION_SUCCESS, GET));
	if (argc > 2)
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (EXECUTION_FAILURE);
	}
	if (!is_numeric(args->next->word->word))
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n",
			args->next->word->word);
		exit(2);
	}
	exit_code = ft_atoi(args->next->word->word);
	exit(exit_code % 256);
}
