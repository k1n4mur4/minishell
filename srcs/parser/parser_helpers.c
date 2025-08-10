/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:30:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 20:30:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

void	process_simple_tokens(t_simple_com *simple, t_token **tokens)
{
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_EOF)
	{
		if ((*tokens)->type == TOKEN_WORD)
			handle_simple_command_word(simple, tokens);
		else if ((*tokens)->type == TOKEN_REDIRECT_IN
			|| (*tokens)->type == TOKEN_REDIRECT_OUT
			|| (*tokens)->type == TOKEN_HEREDOC
			|| (*tokens)->type == TOKEN_APPEND)
			handle_simple_command_redirections(simple, tokens);
		else
			*tokens = (*tokens)->next;
	}
}

t_command	*create_simple_command(t_simple_com *simple)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->type = cm_simple;
	cmd->simple = simple;
	cmd->flags = 0;
	return (cmd);
}

void	cleanup_pipeline_error(t_command *left, t_command *right,
							t_connection *conn)
{
	if (conn)
		free(conn);
	if (left)
		free_command(left);
	if (right)
		free_command(right);
}
