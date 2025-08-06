#include "variables.h"

void	create_variable_tables(void)
{
	t_varlist	*vlist;

	vlist = (t_varlist *)ft_calloc(sizeof(*vlist), 1);
	vlist->list = NULL;
	vlist->list_size = 0;
	vlist->list_len = 0;
	varlist(vlist, SET);
}

t_shell_var	*find_variable(char	*name)
{
	t_varlist	*list;
	size_t		i;

	list = varlist(NULL, GET);
	if (!list || !list->list || !name)
		return (NULL);
	i = 0;
	while (i < list->list_len)
	{
		if (list->list[i] && list->list[i]->name &&
			ft_strcmp(list->list[i]->name, name) == 0)
			return (list->list[i]);
		i++;
	}
	return (NULL);
}

t_shell_var	*create_shell_var(char *str)
{
	t_shell_var	*var;
	char		*equal;

	var = (t_shell_var *)ft_calloc(sizeof(*var), 1);
	if (!var)
		return (NULL);
	equal = ft_strchr(str, '=');
	if (equal)
	{
		var->name = ft_strndup(str, equal - str);
		var->value = ft_strdup(equal + 1);
	}
	else
	{
		var->name = ft_strdup(str);
		var->value = ft_strdup("");
	}
	if (!var->name || !var->value)
	{
		dispose_var(var);
		return (NULL);
	}
	return (var);
}

void	add_variable(t_shell_var *var)
{
	t_varlist	*list;
	t_shell_var	**new_list;
	size_t		new_size;

	list = varlist(NULL, GET);
	if (!list || !var)
		return ;
	if (list->list_len >= list->list_size)
	{
		if (list->list_size == 0)
			new_size = 16;
		else
			new_size = list->list_size * 2;
		new_list = (t_shell_var **)ft_calloc(sizeof(t_shell_var *), new_size);
		if (!new_list)
			return ;
		if (list->list)
		{
			ft_memcpy(new_list, list->list, sizeof(t_shell_var *) * list->list_len);
			free(list->list);
		}
		list->list = new_list;
		list->list_size = new_size;
	}
	list->list[list->list_len] = var;
	list->list_len++;
	if (list->list_len < list->list_size)
		list->list[list->list_len] = NULL;
}

void	set_shell_var(char **env)
{
	t_shell_var	*var;
	int			i;

	i = 0;
	while (env[i])
	{
		var = create_shell_var(env[i]);
		if (var)
			add_variable(var);
		i++;
	}
}

void	add_varlist(t_varlist *varlist, t_varlist *temp)
{
	size_t		i;
	t_shell_var	*new_var;

	if (!varlist || !temp || !temp->list)
		return ;
	i = 0;
	while (i < temp->list_len)
	{
		if (temp->list[i])
		{
			new_var = create_shell_var("");
			if (new_var)
			{
				free(new_var->name);
				free(new_var->value);
				new_var->name = ft_strdup(temp->list[i]->name);
				new_var->value = ft_strdup(temp->list[i]->value);
				if (new_var->name && new_var->value)
					add_variable(new_var);
				else
					dispose_var(new_var);
			}
		}
		i++;
	}
}

int	set_variable(char *name, char *value)
{
	t_shell_var	*var;
	t_shell_var	*new_var;

	var = find_variable(name);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(value);
		if (var->value)
			return (0);
		else
			return (-1);
	}
	new_var = (t_shell_var *)ft_calloc(sizeof(*new_var), 1);
	if (!new_var)
		return (-1);
	new_var->name = ft_strdup(name);
	new_var->value = ft_strdup(value);
	if (!new_var->name || !new_var->value)
	{
		dispose_var(new_var);
		return (-1);
	}
	add_variable(new_var);
	return (0);
}

int	unset_variable(char *name)
{
	t_varlist	*list;
	size_t		i;
	size_t		j;

	list = varlist(NULL, GET);
	if (!list || !list->list || !name)
		return (-1);
	i = 0;
	while (i < list->list_len)
	{
		if (list->list[i] && list->list[i]->name &&
			ft_strcmp(list->list[i]->name, name) == 0)
		{
			dispose_var(list->list[i]);
			j = i;
			while (j < list->list_len - 1)
			{
				list->list[j] = list->list[j + 1];
				j++;
			}
			list->list[list->list_len - 1] = NULL;
			list->list_len--;
			return (0);
		}
		i++;
	}
	return (-1);
}

void	initialize_shell_variables(char **env)
{
	create_variable_tables();
	if (env && *env)
		set_shell_var(env);
}
