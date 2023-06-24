/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_fds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:13:11 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/24 15:18:03 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	get_fds(char **splitted, t_env **env, t_redirects *redir, int fd_heredoc)
{
	if (get_read_write_fds(splitted, env, redir, fd_heredoc) == -1)
	{
		free_matrix(splitted);
		return (-1);
	}
	return (0);
}

int	get_read_write_fds(char **command, t_env **env, t_redirects *redir, \
					int fd_heredoc)
{
	redir->redirects = NULL;
	redir->fd_heredoc = fd_heredoc;
	redir->fd_input = 0;
	redir->fd_output = 1;
	get_redirects(command, env, redir, 0);
	set_fds(redir);
	free_list(&redir->redirects);
	if (redir->fd_input == -1 || redir->fd_output == -1)
	{
		if (redir->fd_input > 0)
			close(redir->fd_input);
		if (redir->fd_output > 1)
			close(redir->fd_output);
		if (redir->fd_heredoc > -1)
			close(redir->fd_heredoc);
		return (-1);
	}
	if (redir->fd_input != redir->fd_heredoc && redir->fd_heredoc > -1)
		close(redir->fd_heredoc);
	return (0);
}

void	get_redirects(char **command, t_env **env, t_redirects *redirect, \
					int exit_status)
{
	char	**temp;
	t_env	*aux;

	if (!command || (exit_status < 0 && !env))
		return ;
	while (*command)
	{
		if (**command && (**command == '>' || **command == '<')
			&& (command[0][1] == -5 || command[0][2] == -5))
		{
			aux = new_node(*command);
			if (!aux)
			{
				free_list(&redirect->redirects);
				return ;
			}
			add_back(&redirect->redirects, aux);
			temp = command - 1;
			free(*command);
			while (*++temp)
				*temp = *(temp + 1);
		}
		else
			command++;
	}
}

int	set_fds(t_redirects *redirect)
{
	t_env	*aux;

	aux = redirect->redirects;
	while (aux)
	{
		if (check_input_fd(aux->var, redirect) == -1)
			return (-1);
		else if (check_output_fd(aux->var, redirect) == -1)
			return (-1);
		else if (check_heredoc_fd(aux->var, redirect) == -1)
			return (-1);
		else if (check_append_fd(aux->var, redirect) == -1)
			return (-1);
		aux = aux->next;
	}
	return (0);
}
