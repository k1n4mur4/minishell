/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 03:45:36 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/06 03:46:11 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_H
# define VAR_H

#include <unistd.h>

typedef struct s_shell_var{
	char	*name;
	char	*value;
}				t_shell_var;

typedef struct t_varlist {
	t_shell_var	**list;
	size_t		list_size;
	size_t		list_len;
}				t_varlist;

#endif