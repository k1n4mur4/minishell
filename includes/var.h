/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 03:45:36 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/06 23:50:21 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_H
# define VAR_H

# include <unistd.h>
# include "libft.h"

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}				t_var;

// despose_var.c
void	dispose_var(t_var *var);
void	dispose_varlist(t_var *var);

// make_var.c
t_var	*alloc_shell_var(void);
t_var	*make_bare_var(char *name);
t_var	*make_var_value(t_var *v, char *value);
t_var	*make_var(char *name, char *value);

#endif