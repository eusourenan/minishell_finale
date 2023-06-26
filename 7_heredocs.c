/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_heredocs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:11:29 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/26 19:21:47 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	set_heredocs_and_execute(char **commands, t_env **env, int exit_status, \
					int *heredocs)
{
	int	ret_check_heredocs;
	int	heredoc;

	ret_check_heredocs = set_heredocs(commands, env, exit_status, heredocs);
	if (ret_check_heredocs != 0)
	{
		close_and_free(heredocs);
		free_matrix(commands);
		return (ret_check_heredocs);
	}
	if (commands[1])
		exit_status = prepare_multiple_commands(commands, env, exit_status, \
								heredocs);
	else
	{
		heredoc = heredocs[0];
		free(heredocs);
		heredocs = NULL;
		exit_status = execute_one_command(commands, env, exit_status, heredoc);
	}
	close_and_free(heredocs);
	return (exit_status);
}

int	set_heredocs(char **commands, t_env **env, int exit_status, int *heredocs)
{
	int		fd;
	int		index;
	char	*copy;
	t_vars	to_free;

	index = 0;
	fd = 0;
	while (commands && commands[index])
	{
		copy = ft_strdup(commands[index]);
		pre_split(copy);
		to_free.commands = commands;
		to_free.heredocs = heredocs;
		to_free.exit_status = exit_status;
		exit_status = get_all_heredocs(copy, env, &fd, &to_free);
		free(copy);
		heredocs[index++] = fd;
		if (exit_status != 0)
			break ;
	}
	return (exit_status);
}

int	get_all_heredocs(char *input, t_env **env, int *fd_hdoc, t_vars *to_free)
{
	int		pid;
	int		pipes[2];
	char	*hdoc_name;
	char	*start;

	pid = 0;
	start = input;
	input = get_heredoc_position(input);
	while (input)
	{	
		input += 2;
		hdoc_name = hdoc_delimiter_pipes_fork(input, pipes, &pid, fd_hdoc);
		if (pid == 0)
		{
			if (child_prepare(&hdoc_name, input, start, to_free))
				return (12);
			prepare_and_exec_hdoc(hdoc_name, env, to_free->exit_status, pipes);
		}
		if (wait_heredoc(pid, fd_hdoc, pipes, to_free))
			return (WEXITSTATUS(to_free->exit_status));
		input = get_heredoc_position(input);
	}
	if (!pid)
		*fd_hdoc = -1;
	return (WEXITSTATUS(to_free->exit_status));
}

char	*get_heredoc_position(char *input)
{
	while (*input)
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		if (*input == '<' && input[1] == '<')
			return (input);
		input++;
	}
	return (NULL);
}

char	*hdoc_delimiter_pipes_fork(char *input, int pipes[], int *pid, \
					int *fd_heredoc)
{
	if (*pid)
		ft_close(*fd_heredoc, STDIN_FILENO);
	while (*input && *input != -1 && *input != -3)
		input++;
	pipe(pipes);
	*pid = fork();
	heredoc_signals(*pid);
	return (input);
}
