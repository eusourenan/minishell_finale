/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23_external_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:13:50 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/24 15:22:44 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	execute_external_command(char **cmd, t_env **env, int exit_status, \
				t_redirects red)
{
	exit_status = fork();
	execution_signals(exit_status);
	if (exit_status == 0)
	{
		rl_clear_history();
		ft_dup2(red.fd_input, STDIN_FILENO);
		ft_dup2(red.fd_output, STDOUT_FILENO);
		if (*cmd && **cmd && !ft_strchr(*cmd, '/'))
			exit_status = set_path(cmd, env, 0);
		exit_status = check_file_path_access(cmd[0], X_OK);
		if (exit_status == 0)
			exit_status = set_envp_and_execute(cmd, env);
		else if (!ft_strchr(*cmd, '/'))
			print_error(*cmd, "command not found ¯\\_(ツ)_/¯", exit_status);
		else
			exit_status = print_file_error(*cmd, exit_status);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		free_matrix(cmd);
		free_list(env);
		exit(exit_status + (exit_status == 125));
	}
	wait(&exit_status);
	return (WEXITSTATUS(exit_status));
}

int	set_path(char **command, t_env **env, int exit_status)
{
	char	**paths;
	char	*path_var;
	int		index;

	path_var = get_value_of_var("PATH", env, exit_status);
	paths = ft_split(path_var, ':');
	if (path_var && !paths)
		return (12);
	index = -1;
	free(path_var);
	while (paths && paths[++index])
	{
		path_var = join_path(paths[index], *command);
		if (!path_var || access(path_var, 0) == 0)
			break ;
		free(path_var);
	}
	index = (paths[index] != NULL);
	free_matrix(paths);
	if (!path_var || !index)
		return (12 * (path_var == NULL));
	free(*command);
	*command = path_var;
	return (0);
}

char	*join_path(char *path_init, char *path_end)
{
	char	*path;

	if (!path_init && !path_end)
		return (NULL);
	path = malloc(ft_strlen(path_init) + ft_strlen(path_end) + 2);
	if (!path)
		return (NULL);
	ft_strlcpy(path, path_init, ft_strlen(path_init) + 1);
	ft_strlcpy(path + ft_strlen(path), "/", 2);
	ft_strlcpy(path + ft_strlen(path), path_end, ft_strlen(path_end) + 1);
	return (path);
}

int	check_file_path_access(char *path, int permission)
{
	struct stat	path_stat;

	if (!path)
		return (127);
	stat(path, &path_stat);
	if (access(path, F_OK) || !ft_strchr(path, '/'))
		return (127);
	if (access(path, permission))
		return (126);
	if (S_ISDIR(path_stat.st_mode))
		return (125);
	return (0);
}

int	set_envp_and_execute(char **command, t_env **env)
{
	char	**envp;

	envp = list_to_pointer(*env);
	if (!envp)
		return (12);
	execve(command[0], command, envp);
	free_matrix(envp);
	return (1);
}
