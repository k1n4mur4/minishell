/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinamura <kinamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:17:32 by kinamura          #+#    #+#             */
/*   Updated: 2025/08/11 14:58:46 by kinamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "command.h"
# include <sys/wait.h>
# include "variables.h"

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

int		wait_for_process(pid_t pid);

void	init_exec_context(t_exec_context *ctx);
void	cleanup_exec_context(t_exec_context *ctx);

void	free_argv_array(char **argv);
void	free_envp_array(char **envp);
void	free_string_array(char **array);

int		count_word_list(t_word_list *words);
int		count_variables(void);
char	*build_path(char *dir, char *command);
char	*build_env_string(char *name, char *value);

void	free_partial_argv(char **argv, int count);
int		fill_argv_array(char **argv, t_word_list *words, int count);
int		fill_envp_array(char **envp, t_var *vars, int count);
char	*search_in_paths(char **paths, char *command);

void	read_heredoc_input(int write_fd, char *delimiter);
int		setup_heredoc_pipe(int pipefd[2]);

int		find_and_validate_command(t_simple_com *cmd, char **command_path);
int		build_command_arrays(t_simple_com *cmd, char ***argv, char ***envp);
int		prepare_external_command(t_simple_com *cmd, char **command_path,
			char ***argv, char ***envp);
int		handle_fork_and_exec(char *command_path, char **argv, char **envp);

#endif