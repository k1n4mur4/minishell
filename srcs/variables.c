#include "variables.h"

t_var	*find_variable(char	*name);
t_var	*make_varlist(t_var	*var);
void	unset_variable(char *name);
t_var	*create_var(char *str);
void	initialize_shell_variables(char **env);

t_var	*find_variable(char	*name)
{
	t_var	*temp;

	temp = ft_var(NULL, GET);
	if (!temp || !name)
		return (NULL);
	while (temp)
	{
		if (temp->name && ft_strcmp(temp->name, name) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_var	*make_varlist(t_var	*var)
{
	t_var	*temp;
	t_var	*varlist;

	if (!var || !var->name)
		return (NULL);
	temp = find_variable(var->name);
	if (temp)
	{
		free(temp->value);
		temp->value = ft_strdup(var->value);
	}
	else
	{
		temp = ft_var(NULL, GET);
		if (!temp)
		{
			temp = ft_var(var, SET);
			return (temp);
		}
		while (temp->next)
			temp = temp->next;
		temp->next = var;
	}
	varlist = ft_var(NULL, GET);
	return (varlist);
}

void	unset_variable(char *name)
{
	t_var	*var;
	t_var	*temp;
	t_var	*prev;

	var = ft_var(NULL, GET);
	if (!var || !name)
		return ;
	temp = var;
	prev = NULL;
	while (temp)
	{
		if (temp->name && ft_strcmp(temp->name, name) == 0)
			break;
		prev = temp;
		temp = temp->next;
	}
	if (temp && temp->name && ft_strcmp(temp->name, name) == 0)
	{
		if (prev == NULL)
			ft_var(temp->next, SET);
		else
			prev->next = temp->next;
		dispose_var(temp);
	}
}

t_var	*create_var(char *str)
{
	t_var	*var;
	char	*name;
	char	*value;
	char	*equal;

	equal = ft_strchr(str, '=');
	if (equal)
	{
		name = ft_strndup(str, equal - str);
		value = ft_strdup(equal + 1);
	}
	else
	{
		name = ft_strdup(str);
		value = NULL;
	}
	var = make_var(name, value);
	if (name)
		free(name);
	if (value)
		free(value);
	return (var);
}

static void	set_var(char **env)
{
	t_var	*var;
	int		i;

	i = 0;
	while (env[i])
	{
		var = create_var(env[i]);
		if (var)
			make_varlist(var);
		i++;
	}
}

void	initialize_shell_variables(char **env)
{
	if (env && *env)
		set_var(env);
}

void	update_var_value(t_var *var, char *new_value)
{
	if (!var)
		return ;
	free(var->value);
	var->value = ft_strdup(new_value);
}
