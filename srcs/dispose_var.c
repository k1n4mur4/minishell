/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:40:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 05:47:08 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var.h"

void	dispose_var(t_var *var);
void	dispose_varlist(t_var *var);

void	dispose_var(t_var *var)
{
	if (var)
	{
		if (var->name)
			free(var->name);
		if (var->value)
			free(var->value);
		free(var);
	}
}

void	dispose_varlist(t_var *var)
{
	t_var	*temp;

	while (var)
	{
		temp = var;
		var = var->next;
		dispose_var(temp);
	}
}
