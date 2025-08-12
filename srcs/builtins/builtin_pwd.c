/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:39:14 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 04:08:53 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_pwd(t_word_list *args)
{
	char	*cwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (EXECUTION_FAILURE);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (EXECUTION_SUCCESS);
}
