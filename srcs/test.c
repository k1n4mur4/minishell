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
	char	*input;
	
	printf("Environment Variable Test Program\n");
	printf("Type 'help' for available commands.\n\n");
	
	while (1)
	{
		input = readline("test> ");
		
		if (!input)
		{
			printf("\nExiting test program...\n");
			break;
		}
		
		if (strlen(input) > 0)
			add_history(input);
		
		execute_command(input);
		
		free(input);
	}
}

void	run_individual_tests(void)
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

void	cmd_env(void)
{
	t_var	*var;
	
	var = ft_var(NULL, GET);
	if (!var)
	{
		printf("No environment variables set.\n");
		return;
	}
	
	while (var)
	{
		if (var->value)
			printf("%s=%s\n", var->name, var->value);
		else
			printf("%s\n", var->name);
		var = var->next;
	}
}

void	cmd_export(char *args)
{
	char	*equal_sign;
	char	*name;
	char	*value;
	t_var	*new_var;
	
	if (!args || strlen(args) == 0)
	{
		cmd_env();
		return;
	}
	
	equal_sign = strchr(args, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		name = args;
		value = equal_sign + 1;
		new_var = make_var(name, value);
		make_varlist(new_var);
		printf("Exported: %s=%s\n", name, value);
	}
	else
	{
		new_var = make_bare_var(args);
		make_varlist(new_var);
		printf("Exported: %s\n", args);
	}
}

void	cmd_unset(char *args)
{
	if (!args || strlen(args) == 0)
	{
		printf("Usage: unset VAR\n");
		return;
	}
	
	unset_variable(args);
	printf("Unset: %s\n", args);
}

void	cmd_echo(char *args)
{
	t_var	*var;
	
	if (!args || strlen(args) == 0)
	{
		printf("\n");
		return;
	}
	
	if (args[0] == '$')
	{
		var = find_variable(args + 1);
		if (var && var->value)
			printf("%s\n", var->value);
		else
			printf("\n");
	}
	else
	{
		printf("%s\n", args);
	}
}

void	print_help(void)
{
	printf("\n========== TEST COMMAND HELP ==========\n");
	printf("Available commands:\n");
	printf("  help                     - Show this help message\n");
	printf("  all                      - Run all tests\n");
	printf("  env                      - Display all environment variables\n");
	printf("  export VAR=value         - Set environment variable\n");
	printf("  export VAR               - Mark variable for export\n");
	printf("  unset VAR                - Remove environment variable\n");
	printf("  echo $VAR                - Display variable value\n");
	printf("  init                     - Test initialize_variables\n");
	printf("  create                   - Test create_var\n");
	printf("  find                     - Test find_variable\n");
	printf("  varlist                  - Test make_varlist\n");
	printf("  test-unset               - Test unset_variable\n");
	printf("  ftvar                    - Test ft_var\n");
	printf("  memory                   - Test memory_management\n");
	printf("  test-env                 - Test env_integration\n");
	printf("  exit                     - Exit test program\n");
	printf("=======================================\n\n");
}

void	execute_command(char *command)
{
	char	*space;
	char	*args;
	
	if (!command)
		return;
	
	space = strchr(command, ' ');
	if (space)
	{
		*space = '\0';
		args = space + 1;
		while (*args == ' ')
			args++;
	}
	else
	{
		args = NULL;
	}
	
	if (strcmp(command, "help") == 0)
		print_help();
	else if (strcmp(command, "env") == 0)
		cmd_env();
	else if (strcmp(command, "export") == 0)
		cmd_export(args);
	else if (strcmp(command, "unset") == 0)
		cmd_unset(args);
	else if (strcmp(command, "echo") == 0)
		cmd_echo(args);
	else if (strcmp(command, "all") == 0)
		run_individual_tests();
	else if (strcmp(command, "init") == 0)
		test_initialize_variables();
	else if (strcmp(command, "create") == 0)
		test_create_var();
	else if (strcmp(command, "find") == 0)
		test_find_variable();
	else if (strcmp(command, "varlist") == 0)
		test_make_varlist();
	else if (strcmp(command, "test-unset") == 0)
		test_unset_variable();
	else if (strcmp(command, "ftvar") == 0)
		test_ft_var();
	else if (strcmp(command, "memory") == 0)
		test_memory_management();
	else if (strcmp(command, "test-env") == 0)
		test_env_integration();
	else if (strcmp(command, "exit") == 0)
	{
		printf("Exiting test program...\n");
		ft_var(NULL, FREE);
		exit(0);
	}
	else if (strlen(command) > 0)
		printf("Unknown command: '%s'. Type 'help' for available commands.\n", command);
}

