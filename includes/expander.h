/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 07:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "command.h"
# include "variables.h"
# include "exit_value.h"
# include "libft.h"

void	expand_variables(t_command *cmd);
char	*expand_string(char *str, int in_double_quotes);
char	*get_variable_value(char *name);

#endif