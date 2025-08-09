/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:17:32 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/10 05:17:33 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "command.h"
# include <sys/wait.h>

# define EXECUTION_SUCCESS	0
# define EXECUTION_FAILURE	1
# define EXECUTION_BUILTIN	2
# define CMD_NOT_FOUND		127
# define PERMISSION_DENIED	126

typedef struct s_exec_context
{
	int		stdin_backup;
	int		stdout_backup;
	int		stderr_backup;
	int		pipe_read;
	int		pipe_write;
}	t_exec_context;

int		execute_command(t_command *cmd);
int		execute_simple_command(t_simple_com *cmd);
int		execute_pipeline(t_command *cmd);
int		execute_connection(t_connection *conn);
int		execute_external_command(t_simple_com *cmd);
int		execute_pipeline_connection(t_connection *conn);
void	execute_child_process(char *path, char **argv, char **envp);

char	*find_command_path(char *command);
char	**build_argv_array(t_word_list *words);
char	**build_envp_array(void);

int		setup_redirections(t_redirect *redirects, t_exec_context *ctx);
int		restore_redirections(t_exec_context *ctx);
int		setup_single_redirect(t_redirect *redir);
int		handle_input_redirect(char *filename);
int		handle_output_redirect(char *filename, int append);
int		handle_heredoc(char *delimiter);

pid_t	create_process(void);
int		wait_for_process(pid_t pid);
void	cleanup_process(pid_t pid);

void	init_exec_context(t_exec_context *ctx);
void	cleanup_exec_context(t_exec_context *ctx);

void	free_argv_array(char **argv);
void	free_envp_array(char **envp);
void	free_string_array(char **array);

int		count_word_list(t_word_list *words);
int		count_variables(void);
char	*build_path(char *dir, char *command);
char	*build_env_string(char *name, char *value);

#endif