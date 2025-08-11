/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:18:15 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 05:18:16 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "command.h"
# include "executor.h"
# include <unistd.h>

typedef int	(*t_builtin_func)(t_word_list *args);

typedef struct s_builtin
{
	char			*name;
	t_builtin_func	func;
}	t_builtin;

int		is_builtin(char *command);
int		execute_builtin(t_simple_com *cmd);

int		builtin_echo(t_word_list *args);
int		builtin_cd(t_word_list *args);
int		builtin_pwd(t_word_list *args);
int		builtin_export(t_word_list *args);
int		builtin_unset(t_word_list *args);
int		builtin_env(t_word_list *args);
int		builtin_exit(t_word_list *args);

int		count_args(t_word_list *args);
int		validate_identifier(const char *str);
void	print_export_var(const char *name, const char *value);
void	print_sorted_env(void);

/* Export sorting functions - builtin_export_sort.c */
int		count_vars(t_var *list);
void	sort_var_array(t_var **arr, int count);
t_var	**create_var_array(int count);

/* CD utility functions - builtin_cd_utils.c */
char	*get_home_directory(void);
char	*get_oldpwd_directory(void);

#endif