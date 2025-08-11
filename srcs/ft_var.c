/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:40:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 04:40:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_var.h"

t_var	*ft_var(t_var *temp, t_type type)
{
	static t_var	*var = NULL;

	if (type == SET)
	{
		var = temp;
	}
	else if (type == GET)
		return (var);
	else if (type == ADD)
		make_varlist(temp);
	else if (type == FREE)
	{
		if (var)
			dispose_varlist(var);
		var = NULL;
	}
	return (var);
}
