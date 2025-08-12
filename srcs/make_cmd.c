/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 20:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_cmd.h"

t_word_desc	*make_bare_word(const char *string)
{
	t_word_desc	*temp;

	temp = alloc_word_desc();
	if (!temp)
		return (NULL);
	if (*string)
	{
		temp->word = ft_strdup(string);
		if (!temp->word)
		{
			free(temp);
			return (NULL);
		}
	}
	else
	{
		temp->word = (char *)malloc(1);
		if (!temp->word)
		{
			free(temp);
			return (NULL);
		}
		temp->word[0] = '\0';
	}
	return (temp);
}

t_word_desc	*make_word(const char *string)
{
	t_word_desc	*temp;

	temp = make_bare_word(string);
	if (!temp)
		return (NULL);
	return (make_word_flags(temp, string));
}

t_word_list	*make_word_list(t_word_desc *word, t_word_list *wlink)
{
	t_word_list	*temp;

	temp = (t_word_list *)malloc(sizeof(t_word_list));
	if (!temp)
		return (NULL);
	temp->word = word;
	temp->next = wlink;
	return (temp);
}

t_command	*make_command(t_command_type type, t_simple_com *pointer)
{
	t_command	*temp;

	temp = (t_command *)malloc(sizeof(t_command));
	if (!temp)
		return (NULL);
	temp->type = type;
	temp->simple = pointer;
	temp->flags = 0;
	temp->line = 0;
	temp->redirect = NULL;
	if (pointer)
		pointer->flags = 0;
	return (temp);
}

t_command	*command_connect(t_command *com1, t_command *com2, int connector)
{
	t_connection	*temp;

	temp = (t_connection *)malloc(sizeof(t_connection));
	if (!temp)
		return (NULL);
	temp->connector = connector;
	temp->first = com1;
	temp->second = com2;
	temp->ignore = 0;
	return (make_command(cm_connection, (t_simple_com *)temp));
}
