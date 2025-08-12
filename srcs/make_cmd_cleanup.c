/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_cleanup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 20:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_cmd.h"

t_command	*clean_simple_command(t_command *command)
{
	t_word_list	*temp_words;
	t_redirect	*temp_redirects;

	if (!command || command->type != cm_simple)
		return (command);
	temp_words = command->simple->words;
	while (temp_words && temp_words->next)
	{
		command->simple->words = temp_words->next;
		temp_words->next = command->simple->words;
		command->simple->words = temp_words;
		temp_words = temp_words->next;
	}
	temp_redirects = command->simple->redirects;
	while (temp_redirects && temp_redirects->next)
	{
		command->simple->redirects = temp_redirects->next;
		temp_redirects->next = command->simple->redirects;
		command->simple->redirects = temp_redirects;
		temp_redirects = temp_redirects->next;
	}
	return (command);
}

t_redirect	*make_redirection(t_redirectee source, t_instruction instruction,
		t_redirectee dest_and_filename, int flags)
{
	t_redirect	*temp;

	temp = (t_redirect *)malloc(sizeof(t_redirect));
	if (!temp)
		return (NULL);
	temp->redirector = source;
	temp->redirectee = dest_and_filename;
	temp->here_doc_eof = NULL;
	temp->instruction = instruction;
	temp->flags = 0;
	temp->rflags = flags;
	temp->next = NULL;
	return (temp);
}

void	dispose_word(t_word_desc *w)
{
	if (!w)
		return ;
	if (w->word)
		free(w->word);
	free(w);
}

void	dispose_words(t_word_list *list)
{
	t_word_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		dispose_word(temp->word);
		free(temp);
	}
}
