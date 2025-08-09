/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 06:10:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 06:10:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

	if (!word)
		return ;
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

static t_redirect	*create_redirect(t_token_type type, char *filename)
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

t_redirect	*parse_redirections(t_token **tokens)
{
	t_redirect	*redirects;
	t_redirect	*current;
	t_redirect	*new_redir;

	redirects = NULL;
	while (*tokens && ((*tokens)->type >= TOKEN_REDIRECT_IN
			&& (*tokens)->type <= TOKEN_APPEND))
	{
		if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
		{
			printf("minishell: syntax error near redirection\n");
			return (redirects);
		}
		new_redir = create_redirect((*tokens)->type,
			(*tokens)->next->value);
		if (!new_redir)
			return (redirects);
		if (!redirects)
		{
			redirects = new_redir;
			current = redirects;
		}
		else
		{
			current->next = new_redir;
			current = new_redir;
		}
		*tokens = (*tokens)->next->next;
	}
	return (redirects);
}

static void	handle_simple_command_word(t_simple_com *simple, t_token **tokens)
{
	t_word_desc	*word;

	word = create_word((*tokens)->value);
	if (word)
		add_word_to_list(&simple->words, word);
	*tokens = (*tokens)->next;
}

static void	handle_simple_command_redirections(t_simple_com *simple, t_token **tokens)
{
	t_redirect	*redirect;
	t_redirect	*temp;

	redirect = parse_redirections(tokens);
	if (!redirect)
		return ;
	if (!simple->redirects)
		simple->redirects = redirect;
	else
	{
		temp = simple->redirects;
		while (temp->next)
			temp = temp->next;
		temp->next = redirect;
	}
}

t_command	*parse_simple_command(t_token **tokens)
{
	t_command		*cmd;
	t_simple_com	*simple;

	if (!tokens || !*tokens)
		return (NULL);
	cmd = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	simple = (t_simple_com *)ft_calloc(1, sizeof(t_simple_com));
	if (!simple)
	{
		free(cmd);
		return (NULL);
	}
	cmd->type = cm_simple;
	cmd->Simple = simple;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
			handle_simple_command_word(simple, tokens);
		else if ((*tokens)->type >= TOKEN_REDIRECT_IN
			&& (*tokens)->type <= TOKEN_APPEND)
			handle_simple_command_redirections(simple, tokens);
		else
			*tokens = (*tokens)->next;
	}
	return (cmd);
}

t_command	*parse_pipeline(t_token **tokens)
{
	t_command		*left;
	t_command		*right;
	t_command		*pipe_cmd;
	t_connection	*conn;

	left = parse_simple_command(tokens);
	if (!left)
		return (NULL);
	if (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		right = parse_pipeline(tokens);
		if (right)
		{
			pipe_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
			conn = (t_connection *)ft_calloc(1, sizeof(t_connection));
			if (pipe_cmd && conn)
			{
				pipe_cmd->type = cm_connection;
				pipe_cmd->Connection = conn;
				conn->first = left;
				conn->second = right;
				conn->connector = '|';
				return (pipe_cmd);
			}
		}
	}
	return (left);
}

t_command	*parse_command_line(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_pipeline(&tokens));
}

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
		if (temp->redirectee.filename)
		{
			if (temp->redirectee.filename->word)
				free(temp->redirectee.filename->word);
			free(temp->redirectee.filename);
		}
		if (temp->here_doc_eof)
			free(temp->here_doc_eof);
		free(temp);
	}
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == cm_simple && cmd->Simple)
	{
		free_word_list(cmd->Simple->words);
		free_redirect(cmd->Simple->redirects);
		free(cmd->Simple);
	}
	else if (cmd->type == cm_connection && cmd->Connection)
	{
		free_command(cmd->Connection->first);
		free_command(cmd->Connection->second);
		free(cmd->Connection);
	}
	free(cmd);
}

void	print_command(t_command *cmd)
{
	t_word_list	*words;
	t_redirect	*redirects;

	if (!cmd)
		return ;
	printf("=== COMMAND ===\n");
	if (cmd->type == cm_simple)
	{
		printf("Type: SIMPLE\n");
		printf("Words: ");
		words = cmd->Simple->words;
		while (words)
		{
			printf("'%s' ", words->word->word);
			words = words->next;
		}
		printf("\nRedirects: ");
		redirects = cmd->Simple->redirects;
		while (redirects)
		{
			printf("<%d:%s> ", redirects->instruction,
				redirects->redirectee.filename->word);
			redirects = redirects->next;
		}
		printf("\n");
	}
	else if (cmd->type == cm_connection)
	{
		printf("Type: PIPELINE\n");
		printf("Left:\n");
		print_command(cmd->Connection->first);
		printf("Right:\n");
		print_command(cmd->Connection->second);
	}
	printf("===============\n");
}