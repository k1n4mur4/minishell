/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 01:42:29 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/06 03:45:53 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	VARIABLES_H
# define	VARIABLES_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "libft.h"
#include "dispose_var.h"
#include "var.h"


// varlist.c
t_varlist	*varlist(t_varlist *temp, t_type type);

// variables.c
void		create_variable_tables(void);
t_shell_var	*find_variable(char *name);
t_shell_var	*create_shell_var(char *str);
void		add_variable(t_shell_var *var);
void		set_shell_var(char **env);
void		add_varlist(t_varlist *varlist, t_varlist *temp);
int			set_variable(char *name, char *value);
int			unset_variable(char *name);
void		initialize_shell_variables(char **env);

#endif
