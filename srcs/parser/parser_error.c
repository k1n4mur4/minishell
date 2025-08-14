/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/15 01:58:16 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "exit_value.h"

static int	get_error_flag(int reset)
{
	static int	error_reported = 0;

	if (reset)
	{
		error_reported = 0;
		return (0);
	}
	if (error_reported)
		return (1);
	error_reported = 1;
	return (0);
}

int	report_syntax_error(t_token *token)
{
	if (get_error_flag(0))
		return (EXECUTION_FAILURE);
	if (!token)
		ft_dprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `newline'\n");
	else
		ft_dprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `%s'\n",
			token->value);
	exit_value(SYNTAX_ERROR, SET);
	return (EXECUTION_FAILURE);
}

void	reset_syntax_error_flag(void)
{
	get_error_flag(1);
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
