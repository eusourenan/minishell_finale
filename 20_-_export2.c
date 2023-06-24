#include "minishell.h" 

int	insert_change_list(char **command, t_env **env)
{
	t_env	*node;

	node = var_is_in_list(*command, env);
	if (node)
	{
		if (ft_strchr(*command, '='))
		{
			free(node->var);
			node->var = *command;
			adjust_commands(&*command);
		}
	}
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
