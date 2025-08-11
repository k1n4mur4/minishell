/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:20:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 22:20:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables_internal.h"

static void	set_var(char **env)
{
	t_var	*var;
	int		i;

	i = 0;
	while (env[i])
	{
		var = create_var(env[i]);
		if (var)
			make_varlist(var);
		i++;
	}
}

static int	get_shlvl_value(void)
{
	t_var	*shlvl_var;
	int		level;

	shlvl_var = find_variable("SHLVL");
	if (shlvl_var && shlvl_var->value)
	{
		level = ft_atoi(shlvl_var->value);
		level++;
	}
	else
		level = 1;
	return (level);
}

static void	update_shlvl_variable(int level)
{
	t_var	*shlvl_var;
	char	*new_value;

	new_value = ft_itoa(level);
	if (!new_value)
		return ;
	shlvl_var = find_variable("SHLVL");
	if (shlvl_var)
	{
		free(shlvl_var->value);
		shlvl_var->value = new_value;
	}
	else
	{
		shlvl_var = make_var("SHLVL", new_value);
		if (shlvl_var)
			make_varlist(shlvl_var);
		free(new_value);
	}
}

static void	initialize_shlvl(void)
{
	int	level;

	level = get_shlvl_value();
	update_shlvl_variable(level);
}

void	initialize_shell_variables(char **env)
{
	if (env && *env)
		set_var(env);
	initialize_shlvl();
}
