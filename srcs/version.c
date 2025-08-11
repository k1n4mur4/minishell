/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:57:03 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/08 00:17:51 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

char	*shell_version_string(void)
{
	static char	tt[32];
	int			i;

	i = 0;
	while (i < 32)
		tt[i++] = '\0';
	if (VERSION)
		ft_memcpy(tt, VERSION, ft_strlen(VERSION));
	return (tt);
}

void	show_shell_version(int extended)
{
	ft_printf("minishell, version %s (%s)\n", shell_version_string(), MACHTYPE);
	if (extended)
	{
		ft_printf("Copyright (C) 2025 Kosuke Inamura\n");
		ft_printf("This is free software under the MIT License.\n");
		ft_printf("You are free to use, copy, modify, merge, publish, "
			"distribute, sublicense, and/or sell copies.\n");
		ft_printf("There is NO WARRANTY, express or implied, "
			"including but not limited to the warranties of merchantability "
			"or fitness for a particular purpose.\n");
	}
}
