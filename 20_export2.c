/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:13:33 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/25 03:30:28 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	insert_or_ignore(char **command, t_env *node)
{
	if (ft_strchr(*command, '='))
	{
		free(node->var);
		node->var = *command;
		adjust_commands(command);
	}
	else
	{
		free(*command);
		adjust_commands(command);
	}
}

int	insert_change_list(char **command, t_env **env)
{
	t_env	*node;

	node = var_is_in_list(*command, env);
	if (node && node != (t_env *)12)
		insert_or_ignore(command, node);
	else if (!node)
	{
		node = ft_calloc(1, sizeof(t_env));
		if (!node)
			return (12);
		node->var = *command;
		adjust_commands(&*command);
		add_back(env, node);
	}
	else
		return (print_format_error("What did YOU do?\n", 12));
	return (0);
}

t_env	*var_is_in_list(char *var, t_env **env)
{
	char	*var_name;
	t_env	*aux;

	var_name = get_var_name(var);
	if (!var_name)
	{
		return ((t_env *) 12);
	}
	aux = *env;
	while (aux)
	{
		if (ft_strncmp(aux->var, var_name, ft_strlen(var) + 1) == '='
			|| !ft_strncmp(aux->var, var_name, ft_strlen(var) + 1))
			break ;
		aux = aux->next;
	}
	free(var_name);
	return (aux);
}

void	adjust_commands(char **command)
{
	while (command && *command)
	{
		*command = command[1];
		command++;
	}
}
