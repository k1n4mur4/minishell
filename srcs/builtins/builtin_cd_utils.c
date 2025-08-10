/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:30:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 20:30:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_home_directory(void)
{
	t_var	*home_var;

	home_var = find_variable("HOME");
	if (home_var && home_var->value)
		return (home_var->value);
	return (NULL);
}

char	*get_oldpwd_directory(void)
{
	t_var	*oldpwd_var;

	oldpwd_var = find_variable("OLDPWD");
	if (oldpwd_var && oldpwd_var->value)
		return (oldpwd_var->value);
	return (NULL);
}
