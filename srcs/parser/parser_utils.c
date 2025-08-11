/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 21:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "shell.h"

t_word_desc	*create_word(char *str)
{
	t_word_desc	*word;

	if (!str)
		return (NULL);
	word = (t_word_desc *)malloc(sizeof(t_word_desc));
	if (!word)
		return (NULL);
	word->word = ft_strdup(str);
	word->flags = 0;
	if (!word->word)
	{
		free(word);
		return (NULL);
	}
	return (word);
}

t_word_list	*create_word_list(t_word_desc *word)
{
	t_word_list	*list;

	if (!word)
		return (NULL);
	list = (t_word_list *)malloc(sizeof(t_word_list));
	if (!list)
		return (NULL);
	list->word = word;
	list->next = NULL;
	return (list);
}

void	add_word_to_list(t_word_list **list, t_word_desc *word)
{
	t_word_list	*new_node;
	t_word_list	*current;

	new_node = create_word_list(word);
	if (!new_node)
		return ;
	if (!*list)
		*list = new_node;
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

void	handle_simple_command_word(t_simple_com *simple, t_token **tokens)
{
	t_word_desc	*word;

	word = create_word((*tokens)->value);
	if (word)
	{
		word->quote_type = (*tokens)->quote_type;
		add_word_to_list(&simple->words, word);
	}
	*tokens = (*tokens)->next;
}

void	handle_simple_command_redirections(t_simple_com *simple,
		t_token **tokens)
{
	t_redirect	*new_redir;

	if (!is_valid_redirect_syntax(*tokens))
	{
		if (*tokens)
			report_syntax_error((*tokens)->next);
		else
			report_syntax_error(NULL);
		if (*tokens)
			*tokens = (*tokens)->next;
		return ;
	}
	new_redir = create_redirect((*tokens)->type, (*tokens)->next->value);
	if (new_redir)
	{
		new_redir->next = simple->redirects;
		simple->redirects = new_redir;
	}
	*tokens = (*tokens)->next->next;
}
