/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 20:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_cmd.h"
#include "shell.h"

t_word_desc	*alloc_word_desc(void)
{
	t_word_desc	*temp;

	temp = (t_word_desc *)malloc(sizeof(t_word_desc));
	if (!temp)
		return (NULL);
	temp->flags = 0;
	temp->word = NULL;
	temp->quote_type = 0;
	return (temp);
}

t_word_desc	*make_word_flags(t_word_desc *w, const char *string)
{
	size_t	i;
	size_t	slen;

	if (!w || !string)
		return (w);
	i = 0;
	slen = ft_strlen(string);
	while (i < slen)
	{
		if (string[i] == '\\')
			i++;
		i++;
	}
	return (w);
}

t_word_desc	*make_word_from_token(int token)
{
	char	tokenizer[2];

	tokenizer[0] = token;
	tokenizer[1] = '\0';
	return (make_word(tokenizer));
}

t_command	*make_simple_command(t_element element, t_command *command,
		int line)
{
	if (command == NULL)
		command = make_bare_simple_command(line);
	if (!command)
		return (NULL);
	if (element.word)
	{
		command->simple->words = make_word_list(element.word,
				command->simple->words);
	}
	else if (element.redirect)
	{
		element.redirect->next = command->simple->redirects;
		command->simple->redirects = element.redirect;
	}
	return (command);
}

t_command	*make_bare_simple_command(int line)
{
	t_command		*command;
	t_simple_com	*temp;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	temp = (t_simple_com *)malloc(sizeof(t_simple_com));
	if (!temp)
	{
		free(command);
		return (NULL);
	}
	temp->flags = 0;
	temp->line = line;
	temp->words = (t_word_list *) NULL;
	temp->redirects = (t_redirect *) NULL;
	command->simple = temp;
	command->type = cm_simple;
	command->redirect = (t_redirect *) NULL;
	command->flags = 0;
	command->line = line;
	return (command);
}
