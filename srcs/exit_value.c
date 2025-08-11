/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:40:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 04:40:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_value.h"

int	exit_value(int exit_value, enum e_type type)
{
	static int	last_command_exit_value = 0;

	if (type == SET)
		last_command_exit_value = exit_value & 255;
	else if (type == GET)
		exit_value = last_command_exit_value;
	return (exit_value);
}
