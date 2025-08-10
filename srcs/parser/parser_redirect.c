/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:15:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 04:15:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_internal.h"

t_redirect	*create_redirect(t_token_type type, char *filename)
{
	t_redirect	*redir;

	redir = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	if (!redir)
		return (NULL);
	if (type == TOKEN_REDIRECT_IN)
		redir->instruction = r_input_direction;
	else if (type == TOKEN_REDIRECT_OUT)
		redir->instruction = r_output_direction;
	else if (type == TOKEN_HEREDOC)
		redir->instruction = r_reading_until;
	else if (type == TOKEN_APPEND)
		redir->instruction = r_appending_to;
	else
	{
		free(redir);
		return (NULL);
	}
	redir->redirectee.filename = create_word(filename);
	if (redir->instruction == r_reading_until && filename)
		redir->here_doc_eof = ft_strdup(filename);
	return (redir);
}

static int	is_redirect_token(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND);
}

static void	add_redirect_to_list(t_redirect **redirects, t_redirect *new_redir)
{
	t_redirect	*current;

	if (!*redirects)
		*redirects = new_redir;
	else
	{
		current = *redirects;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

t_redirect	*parse_redirections(t_token **tokens)
{
	t_redirect	*redirects;
	t_redirect	*new_redir;

	redirects = NULL;
	while (*tokens && is_redirect_token((*tokens)->type))
	{
		if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
		{
			*tokens = (*tokens)->next;
			continue ;
		}
		new_redir = create_redirect((*tokens)->type, (*tokens)->next->value);
		if (new_redir)
			add_redirect_to_list(&redirects, new_redir);
		*tokens = (*tokens)->next->next;
	}
	return (redirects);
}
