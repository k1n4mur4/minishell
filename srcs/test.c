/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:40:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/06 23:59:07 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_initialize_variables(void)
{
	char	*test_env[] = {
		"HOME=/home/test",
		"PATH=/usr/bin:/bin",
		"USER=testuser",
		"SHELL=/bin/bash",
		NULL
	};
	t_var	*var;

	printf("%s test_initialize_variables\n", TEST_START);
	
	ft_var(NULL, FREE);
	initialize_shell_variables(test_env);
	
	var = ft_var(NULL, GET);
	assert(var != NULL);
	
	var = find_variable("HOME");
	assert(var != NULL);
	assert(strcmp(var->name, "HOME") == 0);
	assert(strcmp(var->value, "/home/test") == 0);
	
	var = find_variable("PATH");
	assert(var != NULL);
	assert(strcmp(var->value, "/usr/bin:/bin") == 0);
	
	var = find_variable("USER");
	assert(var != NULL);
	assert(strcmp(var->value, "testuser") == 0);
	
	printf("%s test_initialize_variables\n", TEST_PASS);
	ft_var(NULL, FREE);
}

void	test_create_var(void)
{
	t_var	*var;
	
	printf("%s test_create_var\n", TEST_START);
	
	var = create_var("TEST_VAR=test_value");
	assert(var != NULL);
	assert(strcmp(var->name, "TEST_VAR") == 0);
	assert(strcmp(var->value, "test_value") == 0);
	dispose_var(var);
	
	var = create_var("EMPTY_VALUE=");
	assert(var != NULL);
	assert(strcmp(var->name, "EMPTY_VALUE") == 0);
	assert(var->value == NULL || strlen(var->value) == 0);
	dispose_var(var);
	
	var = create_var("NO_VALUE");
	assert(var != NULL);
	assert(strcmp(var->name, "NO_VALUE") == 0);
	assert(var->value == NULL);
	dispose_var(var);
	
	printf("%s test_create_var\n", TEST_PASS);
}

void	test_find_variable(void)
{
	t_var	*var;
	t_var	*found;
	
	printf("%s test_find_variable\n", TEST_START);
	
	ft_var(NULL, FREE);
	var = make_var("FIND_TEST", "find_value");
	ft_var(var, SET);
	
	found = find_variable("FIND_TEST");
	assert(found != NULL);
	assert(strcmp(found->name, "FIND_TEST") == 0);
	assert(strcmp(found->value, "find_value") == 0);
	
	found = find_variable("NOT_EXIST");
	assert(found == NULL);
	
	found = find_variable(NULL);
	assert(found == NULL);
	
	printf("%s test_find_variable\n", TEST_PASS);
	ft_var(NULL, FREE);
}

void	test_make_varlist(void)
{
	t_var	*var;
	t_var	*var2;
	t_var	*var3;
	t_var	*list;
	t_var	*found;
	
	printf("%s test_make_varlist\n", TEST_START);
	
	ft_var(NULL, FREE);
	
	var = make_var("LIST_VAR1", "value1");
	list = make_varlist(var);
	assert(list != NULL);
	
	found = find_variable("LIST_VAR1");
	assert(found != NULL);
	assert(strcmp(found->value, "value1") == 0);
	
	var2 = make_var("LIST_VAR1", "updated_value");
	list = make_varlist(var2);
	found = find_variable("LIST_VAR1");
	assert(found != NULL);
	assert(strcmp(found->value, "updated_value") == 0);
	
	var3 = make_var("LIST_VAR2", "value2");
	list = make_varlist(var3);
	found = find_variable("LIST_VAR2");
	assert(found != NULL);
	assert(strcmp(found->value, "value2") == 0);
	
	printf("%s test_make_varlist\n", TEST_PASS);
	ft_var(NULL, FREE);
}

void	test_unset_variable(void)
{
	t_var	*var;
	t_var	*var2;
	t_var	*found;
	
	printf("%s test_unset_variable\n", TEST_START);
	
	ft_var(NULL, FREE);
	
	var = make_var("UNSET_TEST", "unset_value");
	ft_var(var, SET);
	
	var2 = make_var("KEEP_TEST", "keep_value");
	make_varlist(var2);
	
	found = find_variable("UNSET_TEST");
	assert(found != NULL);
	
	unset_variable("UNSET_TEST");
	found = find_variable("UNSET_TEST");
	assert(found == NULL);
	
	found = find_variable("KEEP_TEST");
	assert(found != NULL);
	
	unset_variable("NOT_EXIST");
	
	unset_variable(NULL);
	
	printf("%s test_unset_variable\n", TEST_PASS);
	ft_var(NULL, FREE);
}

void	test_ft_var(void)
{
	t_var	*var1;
	t_var	*var2;
	t_var	*result;
	
	printf("%s test_ft_var\n", TEST_START);
	
	ft_var(NULL, FREE);
	
	result = ft_var(NULL, GET);
	assert(result == NULL);
	
	var1 = make_var("FT_VAR1", "ft_value1");
	result = ft_var(var1, SET);
	assert(result == var1);
	
	result = ft_var(NULL, GET);
	assert(result == var1);
	assert(strcmp(result->name, "FT_VAR1") == 0);
	
	var2 = make_var("FT_VAR2", "ft_value2");
	ft_var(var2, ADD);
	
	result = find_variable("FT_VAR2");
	assert(result != NULL);
	assert(strcmp(result->value, "ft_value2") == 0);
	
	ft_var(NULL, FREE);
	result = ft_var(NULL, GET);
	assert(result == NULL);
	
	printf("%s test_ft_var\n", TEST_PASS);
}

void	test_memory_management(void)
{
	t_var	*var;
	t_var	*list;
	int		i;
	char	name[20];
	char	value[20];
	
	printf("%s test_memory_management\n", TEST_START);
	
	ft_var(NULL, FREE);
	
	var = make_var("MEM_TEST", "mem_value");
	assert(var != NULL);
	assert(var->name != NULL);
	assert(var->value != NULL);
	dispose_var(var);
	
	list = NULL;
	for (i = 0; i < 10; i++)
	{
		sprintf(name, "MEM_VAR%d", i);
		sprintf(value, "value%d", i);
		var = make_var(name, value);
		var->next = list;
		list = var;
	}
	
	while (list)
	{
		var = list;
		list = list->next;
		dispose_var(var);
	}
	
	var = make_bare_var("BARE_VAR");
	assert(var != NULL);
	assert(strcmp(var->name, "BARE_VAR") == 0);
	assert(var->value == NULL);
	
	var = make_var_value(var, "new_value");
	assert(strcmp(var->value, "new_value") == 0);
	
	var = make_var_value(var, "updated_value");
	assert(strcmp(var->value, "updated_value") == 0);
	
	dispose_var(var);
	
	printf("%s test_memory_management\n", TEST_PASS);
}

void	test_env_integration(void)
{
	char	*test_env[] = {
		"VAR1=value1",
		"VAR2=value2",
		"VAR3=value3",
		"EMPTY=",
		"PATH=/usr/local/bin:/usr/bin:/bin",
		NULL
	};
	t_var	*var;
	t_var	*new_var;
	int		count;
	
	printf("%s test_env_integration\n", TEST_START);
	
	ft_var(NULL, FREE);
	initialize_shell_variables(test_env);
	
	var = ft_var(NULL, GET);
	count = 0;
	while (var)
	{
		count++;
		var = var->next;
	}
	assert(count >= 4);
	
	var = find_variable("VAR1");
	assert(var != NULL);
	assert(strcmp(var->value, "value1") == 0);
	
	var = find_variable("EMPTY");
	assert(var != NULL);
	assert(var->value == NULL || strlen(var->value) == 0);
	
	new_var = make_var("NEW_VAR", "new_value");
	make_varlist(new_var);
	
	var = find_variable("NEW_VAR");
	assert(var != NULL);
	assert(strcmp(var->value, "new_value") == 0);
	
	new_var = make_var("VAR1", "updated_value1");
	make_varlist(new_var);
	
	var = find_variable("VAR1");
	assert(var != NULL);
	assert(strcmp(var->value, "updated_value1") == 0);
	
	unset_variable("VAR2");
	var = find_variable("VAR2");
	assert(var == NULL);
	
	var = find_variable("VAR3");
	assert(var != NULL);
	
	printf("%s test_env_integration\n", TEST_PASS);
	ft_var(NULL, FREE);
}

void	run_all_tests(void)
{
	printf("\n========== ENVIRONMENT VARIABLE TESTS ==========\n\n");
	
	test_initialize_variables();
	test_create_var();
	test_find_variable();
	test_make_varlist();
	test_unset_variable();
	test_ft_var();
	test_memory_management();
	test_env_integration();
	
	printf("\n========== ALL TESTS PASSED ==========\n\n");
}

// int	main(void)
// {
// 	run_all_tests();
// 	return (0);
// }