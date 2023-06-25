/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:10:13 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/25 15:40:49 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(t_env *env)
{
	int		level;
	char	*char_level;
	char	*join;

	while (env)
	{
		if (ft_strncmp(env->var, "SHLVL", 6) == '=')
			break ;
		env = env->next;
	}
	if (env)
	{
		level = ft_atoi(env->var + 6);
		char_level = ft_itoa(level + 1);
		if (!char_level)
			return ;
		join = ft_strjoin("SHLVL=", char_level);
		free(char_level);
		if (!join)
			return ;
		free(env->var);
		env->var = join;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*list;
	int		ret;

	if (argc > 1 || argv[1])
	{
		ft_putendl_fd("EXECUTE ME PROPERLY, YOU ASSHOLE!!! ┗|｀O′|┛", 2);
		return (2);
	}
	list = pointer_to_list(envp);
	if (!list)
	{
		ft_putendl_fd("You don't have space, bro! (っ˘̩╭╮˘̩)っ", 2);
		return (ENOMEM);
	}
	set_shlvl(list);
	ret = minishell(&list);
	free_list(&list);
	rl_clear_history();
	ft_putendl_fd("exit", 1);
	return (ret);
}
