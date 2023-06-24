#include "minishell.h" 

int	ft_cd(char **command, t_redirects redir, t_env **env, int exit_status)
{
	char	*home;

	if (!command)
		return (12);
	if (!command[1])
	{
		home = get_value_of_var("HOME", env, exit_status);
		if (!home)
			return (print_error(*command, "HOME not set", 1));
	}
	else if (command[2])
		return (print_error(*command, "too many arguments", 1));
	else
		home = command[1];
	if (chdir(home))
	{
		print_file_error(home, check_file_path_access(home, X_OK));
		return (1);
	}
	return (0);
	(void)redir;
}
