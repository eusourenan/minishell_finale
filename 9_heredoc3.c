/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_heredoc3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:12:19 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/24 15:17:01 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	wait_heredoc(int pid, int *fd_heredoc, int pipes[], t_vars *to_free)
{
	waitpid(pid, &to_free->exit_status, 0);
	ft_close(pipes[1], STDIN_FILENO);
	*fd_heredoc = pipes[0];
	if (WIFSIGNALED(to_free->exit_status))
		return (1);
	return (0);
}

void	execute_heredoc(int fd, int expandble, char *key, t_env **env)
{
	char	*input;
	char	*error;

	while (1)
	{
		input = readline("heredoc > ");
		if (!input)
		{
			error = ft_strjoin("here-document delimited by end-of-line but, "\
			"wanted `", key);
			if (!error)
				error = "end-of-line inserted from nowhere";
			print_error("warning", error, 0);
			if (!ft_strncmp(error, "end", 3))
				free(error);
			return ;
		}
		if (ft_strcmp(key, input) == 0)
			break ;
		if (expandble >> 8 == 0)
			input = expand_variables(input, env, expandble);
		ft_putendl_fd(input, fd);
		free(input);
	}
	free(input);
}

void	finish_heredoc(char *heredoc_name, t_env **env, int pipes[])
{
	free_list(env);
	free(heredoc_name);
	ft_close(pipes[0], STDIN_FILENO);
	ft_close(pipes[1], STDOUT_FILENO);
}

void	close_and_free(int *heredocs)
{
	int	index;

	index = 0;
	while (heredocs && heredocs[index] && heredocs[index] != -2)
	{
		if (heredocs[index] != -1)
			ft_close(heredocs[index], STDIN_FILENO);
		index++;
	}
	free(heredocs);
}
