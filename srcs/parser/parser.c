/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 06:10:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 04:10:02 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

t_command	*parse_simple_command(t_token **tokens)
{
	t_simple_com	*simple;
	t_command		*cmd;

	simple = (t_simple_com *)ft_calloc(1, sizeof(t_simple_com));
	if (!simple)
		return (NULL);
	process_simple_tokens(simple, tokens);
	cmd = create_simple_command(simple);
	if (!cmd)
	{
		free(simple);
		return (NULL);
	}
	return (cmd);
}

static t_command	*create_pipeline_connection(t_command *left,
		t_command *right)
{
	t_connection	*conn;
	t_command		*cmd;

	conn = (t_connection *)malloc(sizeof(t_connection));
	if (!conn)
	{
		cleanup_pipeline_error(left, right, NULL);
		return (NULL);
	}
	conn->first = left;
	conn->second = right;
	conn->connector = '|';
	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
	{
		cleanup_pipeline_error(left, right, conn);
		return (NULL);
	}
	cmd->type = cm_connection;
	cmd->connection = conn;
	cmd->flags = 0;
	return (cmd);
}

t_command	*parse_pipeline(t_token **tokens)
{
	t_command	*left;
	t_command	*right;

	left = parse_simple_command(tokens);
	if (!left)
		return (NULL);
	if (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		right = parse_pipeline(tokens);
		if (!right)
		{
			free_command(left);
			return (NULL);
		}
		return (create_pipeline_connection(left, right));
	}
	return (left);
}

t_command	*parse_command_line(t_token *tokens)
{
	return (parse_pipeline(&tokens));
}
