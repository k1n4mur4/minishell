/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:20:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 22:20:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_INTERNAL_H
# define VARIABLES_INTERNAL_H

# include "variables.h"

/* Variable utility functions - variables_utils.c */
t_var	*create_var(char *str);
void	initialize_shell_variables(char **env);

#endif