/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:11:42 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/25 02:46:14 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <err.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <bsd/string.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft.h"

struct s_env
{
	char			*var;
	struct s_env	*next;
};
typedef struct s_env		t_env;

struct s_redirects
{
	t_env	*redirects;
	int		fd_heredoc;
	int		fd_input;
	int		fd_output;
};
typedef struct s_redirects	t_redirects;

struct s_vars
{
	char	**commands;
	int		*heredocs;
	int		exit_status;
};
typedef struct s_vars		t_vars;

// _signals.c
void	init_signals(void);
void	redo_readline(int signal);
void	heredoc_signals(int pid);
void	free_heredoc(int signal);
void	execution_signals(int pid);

// _split_commands.c
char	**split_commands(char *input);
char	**insert_command(char *input, char **commands);
int		count_pipes(char *input);

// main.c
void	set_shlvl(t_env *env);
int		main(int argc, char **argv, char **envp);

// env.c
char	**list_to_pointer(t_env *list);
t_env	*pointer_to_list(char **envp);

// list.c
void	free_node(t_env **list);
void	free_list(t_env **list);
void	add_back(t_env **list, t_env *node);
t_env	*new_node(char *value);
size_t	list_size(t_env *list);

// minishell.c
char	*ft_readline(char *text);
int		minishell(t_env **env);

// input_checker
int		has_input_error(char *input);
int		ft_is_only_spaces(char *input);
int		ft_has_invalid_pipe(char *input);
int		has_unclosed_quotes(char *input);
int		has_redirect_error(char *input);

// normalize_input
void	find_comment(char *input);
void	ft_adjust_delimiters(char *s);

// normalize_command
int		normalize_command(char *input, t_env **env, int exit_status);
int		number_of_redirects(char *str);
char	*redirect(char *str);
char	*put_minus_five_after_redirects(char *str);
int		count_commands(char **cmd);

// heredocs
int		set_heredocs_and_execute(char **commands, t_env **env, \
					int exit_status, int *heredocs);
int		set_heredocs(char **commands, t_env **env, int exit_status, \
					int *heredocs);
int		get_all_heredocs(char *input, t_env **env, int *fd_hdoc, \
					t_vars *to_free);
char	*get_heredoc_position(char *input);
char	*hdoc_delimiter_pipes_fork(char *input, int pipes[], int *pid, \
					int *fd_heredoc);

// heredocs2
int		child_prepare(char **heredoc_name, char *input, char *start, \
					t_vars *to_free);
void	just_clear_history_and_free(t_vars *to_free);
void	prepare_and_exec_hdoc(char *heredoc_name, t_env **env, int pid, \
					int pipes[]);
void	remove_quotes_from_heredoc(char *heredoc_name);
void	set_and_free_heredoc(int pipes[], char *str, t_env **env);

// heredocs3
int		wait_heredoc(int pid, int *fd_heredoc, int pipes[], t_vars *to_free);
void	execute_heredoc(int fd, int expandble, char *key, t_env **env);
void	finish_heredoc(char *heredoc_name, t_env **env, int pipes[]);
void	close_and_free(int *heredocs);

// multiple_commands
int		prepare_multiple_commands(char **commands, t_env **env, \
					int exit_status, int *heredocs);
int		start_fork_pids(char **commands, t_vars *command);
void	start_pipes(char **commands, int pipes[], t_vars *command, int actual);
void	initial_adjust_of_commands(int pipes[], int bkp_input, \
					t_vars *command, int actual_command);
int		pre_execution(char **commands, t_vars *command, int *heredocs, \
					int actual);

// multiple_commands1
int		close_heredocs_except_in_index(int *heredocs, int index_to_save);
int		free_commands_and_heredocs(char **commands, int *heredocs, \
					int exit_status);
void	finishing_command(t_env **env, int exit_status);
void	parent_fds_control(int pipes[], int *bkp_input, char **commands, \
					int actual_command);
void	wait_all_childs(int *fork_pids, int *exit_status);

// one_command
int		execute_one_command(char **command, t_env **env, int exit_s, \
					int fd_heredoc);
void	pre_split(char *input);
int		is_only_pre_split(char *command);
int		has_vars(char *command);
void	free_all(char **splitted, t_redirects redirect);

// prepare_expansions
int		expand_all(char **commands, t_env **env, int exit_status);
char	*make_expansions_and_remove_quotes(char *input, t_env **env, \
					int exit_status);
void	ft_modify_quotemarks_to_remove(char *input, char *set);
int		get_index(char c, char *s);
void	ft_removing_modified_quotemarks(char *input, char *set);

// var_expansions
char	*find_var(char *input);
char	*get_var_name(char *start);
char	*get_value_of_var(char *var, t_env **env, int exit_status);
char	*expand_variables(char *input, t_env **env, int exit_status);

// fds
int		get_fds(char **splitted, t_env **env, t_redirects *redir, \
					int fd_heredoc);
int		get_read_write_fds(char **command, t_env **env, t_redirects *redir, \
					int fd_heredoc);
void	get_redirects(char **command, t_env **env, t_redirects *redirect, \
					int exit_status);
int		set_fds(t_redirects *redirect);

// check_fds
int		check_input_fd(char *var, t_redirects *redirect);
int		check_output_fd(char *var, t_redirects *redirect);
int		check_heredoc_fd(char *var, t_redirects *redirect);
int		check_append_fd(char *var, t_redirects *redirect);

// builtins
void	*set_builtin(char **command);
int		ft_help(char **command, t_redirects redir, t_env **env, \
					int exit_status);
int		ft_echo(char **command, t_redirects redir, t_env **env, \
					int exit_status);
int		ft_pwd(char **command, t_redirects redir, t_env **env, \
					int exit_status);
int		ft_env(char **command, t_redirects redir, t_env **env, \
					int exit_status);

// exit
long	ft_atoll(char *s);
int		numb_fits_max_long(char *numb_begin, int sign);
int		is_valid_number(char *s);
void	print_exit_error(char *argument);
int		ft_exit(char **command, t_redirects redir, t_env **env, \
					int exit_status);

// export
int		ft_export(char **command, t_redirects redir, t_env **env, \
					int exit_status);
void	print_export(t_env *env, int output_fd);
int		ft_check_var_name(char *start_var_name);

// export2
int		insert_change_list(char **command, t_env **env);
t_env	*var_is_in_list(char *var, t_env **env);
void	adjust_commands(char **command);

// unset
void	free_node_from_list(t_env *node, t_env **list);
int		ft_unset(char **command, t_redirects redir, t_env **env, \
					int exit_status);

// cd
int		ft_cd(char **command, t_redirects redir, t_env **env, int exit_status);

// external_command
int		execute_external_command(char **cmd, t_env **env, int exit_status, \
					t_redirects red);
int		set_path(char **command, t_env **env, int exit_status);
char	*join_path(char *path_init, char *path_end);
int		check_file_path_access(char *path, int permission);
int		set_envp_and_execute(char **command, t_env **env);

// print_functions
int		print_format_error(char *message, int exit_status);
int		print_error(char *command, char *error, int exit_status);
int		print_file_error(char *path, int code);
int		print_arg_error(char *command, char *arg, char *error, \
					int exit_status);

// utils
void	free_matrix(char **matrix);
int		ft_is_in_set(char c, char const *set);
int		has_quotes(char *s);
int		ft_strcmp(char *s1, char *s2);

// dup_and_close
void	ft_dup2(int new, int old);
void	ft_close(int fd, int check);

// tilde_expansions
int		ft_check_before_tilde(char *input, char *start);
int		ft_check_after_tilde(char *input);
char	*make_string(char *start, char *tilde_position, t_env **env, \
					int exit_status);
char	*tilde_expansion(char *input, t_env **env);

#endif