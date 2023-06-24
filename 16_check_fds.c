/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_check_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:13:17 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/24 15:18:17 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	check_input_fd(char *var, t_redirects *redirect)
{
	if (*var == '<' && var[1] != '<')
	{
		if (redirect->fd_input != 0
			&& redirect->fd_input != redirect->fd_heredoc)
			close(redirect->fd_input);
		if (!var[2])
		{
			redirect->fd_input = -1;
			return (print_format_error("Ambiguous redirect\n", -1));
		}
		redirect->fd_input = open(var + 2, O_RDONLY);
		if (redirect->fd_input == -1)
		{
			print_file_error(var + 2, check_file_path_access(var + 2, R_OK));
			return (-1);
		}
	}
	return (0);
}

int	check_output_fd(char *var, t_redirects *redirect)
{
	if (*var == '>' && var[1] != '>')
	{
		if (redirect->fd_output != 1)
			close(redirect->fd_output);
		if (!var[2])
		{
			redirect->fd_output = -1;
			return (print_format_error("Ambiguous redirect\n", -1));
		}
		redirect->fd_output = open(var + 2, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (redirect->fd_output == -1)
		{
			print_file_error(var + 2, check_file_path_access(var + 2, W_OK));
			return (-1);
		}
	}
	return (0);
}

int	check_heredoc_fd(char *var, t_redirects *redirect)
{
	if (*var == '<' && var[1] == '<')
	{
		if (redirect->fd_input != 0
			&& redirect->fd_input != redirect->fd_heredoc)
			close(redirect->fd_input);
		redirect->fd_input = redirect->fd_heredoc;
	}
	return (0);
}

int	check_append_fd(char *var, t_redirects *redirect)
{
	if (*var == '>' && var[1] == '>')
	{
		if (redirect->fd_output != 1)
			close(redirect->fd_output);
		if (!var[3])
		{
			redirect->fd_output = -1;
			return (print_format_error("Ambiguous redirect\n", -1));
		}
		redirect->fd_output = open(var + 3, O_CREAT | O_APPEND | O_WRONLY, \
									0644);
		if (redirect->fd_output == -1)
		{
			print_file_error(var + 3, check_file_path_access(var + 3, W_OK));
			return (-1);
		}
	}
	return (0);
}
