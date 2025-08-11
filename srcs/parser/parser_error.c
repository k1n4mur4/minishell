/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 20:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "shell.h"

int	report_syntax_error(t_token *token)
{
	if (!token)
		ft_dprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `newline'\n");
	else
		ft_dprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `%s'\n",
			token->value);
	return (EXECUTION_FAILURE);
}

int	is_valid_redirect_syntax(t_token *current)
{
	if (!current)
		return (0);
	if (current->type == TOKEN_REDIRECT_IN
		|| current->type == TOKEN_REDIRECT_OUT
		|| current->type == TOKEN_HEREDOC || current->type == TOKEN_APPEND)
	{
		if (!current->next || current->next->type != TOKEN_WORD)
			return (0);
	}
	return (1);
}
