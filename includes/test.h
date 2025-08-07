/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:40:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/06 23:59:07 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "variables.h"
# include "ft_var.h"
# include "libft.h"

# define TEST_PASS "\033[32m[PASS]\033[0m"
# define TEST_FAIL "\033[31m[FAIL]\033[0m"
# define TEST_START "\033[36m[TEST]\033[0m"

void	test_initialize_variables(void);
void	test_create_var(void);
void	test_find_variable(void);
void	test_make_varlist(void);
void	test_unset_variable(void);
void	test_ft_var(void);
void	test_memory_management(void);
void	test_env_integration(void);
void	run_all_tests(void);
void	run_individual_tests(void);
void	print_help(void);
void	execute_command(char *command);
void	cmd_env(void);
void	cmd_export(char *args);
void	cmd_unset(char *args);
void	cmd_echo(char *args);

#endif