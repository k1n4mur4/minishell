/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:42:29 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/07 00:07:30 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	VARIABLES_H
# define	VARIABLES_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "var.h"
#include "ft_var.h"


// variables.c
t_var	*find_variable(char	*name);
t_var	*make_varlist(t_var	*var);
void	unset_variable(char *name);
t_var	*create_var(char *str);
void	initialize_shell_variables(char **env);

#endif
