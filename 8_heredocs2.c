/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_heredocs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:12:10 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/24 15:16:55 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	child_prepare(char **heredoc_name, char *input, char *start, \
					t_vars *to_free)
{
	just_clear_history_and_free(to_free);
	*heredoc_name = ft_substr(input + 1, 0, *heredoc_name - input - 1);
	if (!*heredoc_name)
		return (12);
	free(start);
	return (0);
}

void	just_clear_history_and_free(t_vars *to_free)
{
	rl_clear_history();
	free_matrix(to_free->commands);
	close_and_free(to_free->heredocs);
}

void	prepare_and_exec_hdoc(char *heredoc_name, t_env **env, int pid, \
					int pipes[])
{
	pid = (has_quotes(heredoc_name) << 8) + pid;
	remove_quotes_from_heredoc(heredoc_name);
	set_and_free_heredoc(pipes, heredoc_name, env);
	execute_heredoc(pipes[1], pid, heredoc_name, env);
	finish_heredoc(heredoc_name, env, pipes);
	exit(0);
}

void	remove_quotes_from_heredoc(char *heredoc_name)
{
	ft_modify_quotemarks_to_remove(heredoc_name, "'\"");
	ft_removing_modified_quotemarks(heredoc_name, "'\"");
}

void	set_and_free_heredoc(int pipes[], char *str, t_env **env)
{
	static int		*p;
	static char		*s;
	static t_env	*e;

	if (!pipes && !str && !env)
	{
		close(p[0]);
		close(p[1]);
		free(s);
		free_list(&e);
		exit(127);
	}
	p = pipes;
	s = str;
	e = *env;
}
