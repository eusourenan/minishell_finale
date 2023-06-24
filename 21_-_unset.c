#include "minishell.h" 

void	free_node_from_list(t_env *node, t_env **list)
{
	t_env	*aux;

	aux = *list;
	if (aux == node)
	{
		*list = (*list)->next;
		free(node->var);
		free(node);
	}
	else
	{
		while (aux->next)
		{
			if (aux->next == node)
				break ;
			aux = aux->next;
		}
		aux->next = aux->next->next;
		free(node->var);
		free(node);
	}
}

int	ft_unset(char **command, t_redirects redir, t_env **env, int exit_status)
{
	t_env	*node;

	exit_status = 0;
	if (!command)
		return (12);
	while (*++command)
	{
		if (ft_check_var_name(*command))
		{
			node = var_is_in_list(*command, env);
			if (node)
				free_node_from_list(node, env);
		}
		else
		{
			exit_status = 1;
			print_arg_error("unset", *command, "not a valid identifier", 1);
		}
	}
	return (exit_status);
	(void)redir;
}
