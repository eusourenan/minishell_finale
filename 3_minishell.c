/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:10:31 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/24 15:22:57 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(char *text)
{
	char	*bkp;
	char	*line;

	bkp = "> ";
	line = malloc(ft_strlen(text) + 3);
	if (!line || !text)
		return (readline(bkp));
	ft_strlcpy(line, text, ft_strlen(text) + 1);
	ft_strlcpy(line + ft_strlen(line), bkp, 3);
	bkp = readline(line);
	free(line);
	return (bkp);
}

int	minishell(t_env **env)
{
	char	*input;
	char	*cwd;
	int		exit_status;

	input = NULL;
	exit_status = 0;
	while (1)
	{
		init_signals();
		cwd = getcwd(NULL, 0);
		input = ft_readline(cwd);
		free(cwd);
		if (has_input_error(input))
		{
			if (!input)
				break ;
			if (*input)
				ft_putendl_fd("Do you really know how to type a command?"\
			" ヽ( `д´*)ノ", 2);
			free(input);
			continue ;
		}
		exit_status = normalize_command(input, env, exit_status);
	}
	return (exit_status);
}
