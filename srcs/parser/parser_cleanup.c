/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 21:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_word_list(t_word_list *list)
{
	t_word_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->word)
		{
			if (temp->word->word)
				free(temp->word->word);
			if (temp->word->segments)
				free(temp->word->segments);
			free(temp->word);
		}
		free(temp);
	}
}

void	free_redirect(t_redirect *redir)
{
	t_redirect	*temp;

	while (redir)
	{
		temp = redir;
		redir = redir->next;
		if (temp->redirectee.filename && temp->redirectee.filename->word)
			free(temp->redirectee.filename->word);
		if (temp->redirectee.filename)
			free(temp->redirectee.filename);
		if (temp->here_doc_eof)
			free(temp->here_doc_eof);
		free(temp);
	}
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == cm_simple && cmd->simple)
	{
		free_word_list(cmd->simple->words);
		free_redirect(cmd->simple->redirects);
		free(cmd->simple);
	}
	else if (cmd->type == cm_connection && cmd->connection)
	{
		free_command(cmd->connection->first);
		free_command(cmd->connection->second);
		free(cmd->connection);
	}
	free(cmd);
}
