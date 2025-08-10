/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 22:00:00 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 22:00:00 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_INTERNAL_H
# define REDIRECT_INTERNAL_H

# include "executor.h"
# include "shell.h"

/* Heredoc helper functions - redirect_heredoc.c */
void	write_heredoc_line(int pipefd, char *line);
int		read_heredoc_interactive(int pipefd, char *delimiter);
int		read_heredoc_non_interactive(int pipefd, char *delimiter);

#endif