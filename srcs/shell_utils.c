/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:30:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 05:46:29 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"
#include "libft.h"

char	*get_prompt(void)
{
	t_var	*ps1_var;
	char	*prompt;

	ps1_var = find_variable("PS1");
	if (ps1_var && ps1_var->value)
		prompt = ps1_var->value;
	else
		prompt = "minishell$ ";
	return (prompt);
}

void	shell_initialize(void)
{
	t_var	*ps1_var;

	ps1_var = find_variable("PS1");
	if (ps1_var)
	{
		free(ps1_var->value);
		ps1_var->value = ft_strdup("minishell$ ");
	}
	else
	{
		ps1_var = make_var("PS1", "minishell$ ");
		if (ps1_var)
			make_varlist(ps1_var);
	}
}
