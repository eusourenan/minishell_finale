#include "minishell.h" 

int	ft_export(char **command, t_redirects redir, t_env **env, int exit_status)
{
	exit_status = 0;
	if (!command)
		return (12);
	if (!command[1])
		print_export(*env, redir.fd_output);
	else if (*++command)
	{
		while (*command)
		{
			if (ft_check_var_name(*command))
			{
				if (insert_change_list(&*command, env) == 12)
					return (print_format_error("No more memory", 12));
			}
			else
			{
				exit_status = 1;
				print_arg_error("export", *command++, "not a valid identifier"\
										, 1);
			}
		}
	}
	return (exit_status);
}

void	print_export(t_env *env, int output_fd)
{
	int i;

	while (env)
	{
		ft_putstr_fd("declare -x ", output_fd);
		i = 0;
		while(env->var[i] != '=' && env->var[i] != '\0')
			ft_putchar_fd(env->var[i++], output_fd);
		if (env->var[i] != '\0')
		{
			write(output_fd, "=", 1);
			write(output_fd, "\"", 1);
			i++;
			while(env->var[i] != '\0')
			{
				ft_putchar_fd(env->var[i], output_fd);
				i++;
			}
			write(output_fd, "\"", 1);
		}
		write(output_fd, "\n", 1);
		env = env->next;
	}
}

int	ft_check_var_name(char *start_var_name)
{
	char *end_var_name;

	end_var_name = start_var_name;
	while (*end_var_name != '=' && *end_var_name)
		end_var_name++;
	if (!start_var_name || !*start_var_name || end_var_name == start_var_name)
		return (0);
	if (start_var_name > end_var_name)
		return (0);
	if (ft_isalpha(*start_var_name) || *start_var_name == '_')
	{
		start_var_name++;
		while (ft_isalnum(*start_var_name) || *start_var_name == '_')
			start_var_name++;
	}
	else
		return (0);
	if (start_var_name == end_var_name)
		return (1);
	return (0);
}
