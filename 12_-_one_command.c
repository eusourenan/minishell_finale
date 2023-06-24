#include "minishell.h" 

int	execute_one_command(char **cmd, t_env **env, int exit_s, int fd_heredoc)
{
	char		**splitted;
	int			(*builtin)(char **, t_redirects, t_env **, int);
	t_redirects	redirect;

	pre_split(*cmd);
	splitted = ft_split(*cmd, -3);
	if (!splitted)
		return (12);
	free_matrix(cmd);
	redirect.fd_input = expand_all(splitted, env, exit_s);
	if (redirect.fd_input == 12 || !*splitted)
	{
		ft_close(fd_heredoc, -1);
		free_matrix(splitted);
		return (1 * redirect.fd_input);
	}
	if (get_fds(splitted, env, &redirect, fd_heredoc) == -1)
		return (1);
	builtin = set_builtin(splitted);
	if (set_builtin(splitted) != NULL)
		exit_s = builtin(splitted, redirect, env, exit_s);
	else if (*splitted)
		exit_s = execute_external_command(splitted, env, exit_s, redirect);
	free_all(splitted, redirect);
	return (exit_s);
}

void	pre_split(char *input)
{
	if (!input || !*input)
		return ;
	while (*input)
	{
		if (*input == '"' || *input == '\'')
			input = ft_strchr(input + 1, *input);
		if (*input == ' ')
			*input = -3;
		input++;
	}
}

int	is_only_pre_split(char *command)
{
	while (command && *command == -3)
		command++;
	return (!*command);
}

int	has_vars(char *command)
{
	while (command && *command)
	{
		if (*command == '\'')
		{
			while (*command && *command != '\'')
				command++;
		}
		if (*command == '"')
		{
			while (*command && *command != '"')
			{
				if (*command == '$' && (command[1] == '_'
					|| ft_isalpha(command[1])))
					return (1);
				command++;
			}
		}
		if (*command == '$' && (command[1] == '_' || ft_isalpha(command[1])))
					return (1);
		command++;
	}
	return (0);
}

void	free_all(char **splitted, t_redirects redirect)
{
	free_matrix(splitted);
	ft_close(redirect.fd_input, STDIN_FILENO);
	ft_close(redirect.fd_output, STDOUT_FILENO);
}
