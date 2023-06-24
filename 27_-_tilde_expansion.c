#include "minishell.h" 

int	ft_check_before_tilde(char *input, char *start)
{
	if (!input || input == start)
		return (0);
	if (input < start)
		return (1);
	if (*input == '=')
	{
		if (ft_isalpha(*start) || *start == '_')
		{
			start++;
			while (ft_isalnum(*start) || *start == '_')
				start++;
		}
		else
			return (0);
		if (start == input)
			return (1);
	}
	return (0);
}

int	ft_check_after_tilde(char *input)
{
	if (!input)
		return (0);
	if (!*input)
		return (1);
	if (*input == '/' || *input == ':')
		return (1);
	return (0);
}

char	*make_string
(char *start, char *tilde_position, t_env **env, int exit_status)
{
	char	*string;
	char	*expansion;

	expansion = get_value_of_var("HOME", env, exit_status);
	if (!expansion)
		return (start);
	string = malloc(tilde_position - start + ft_strlen(expansion) + 
				ft_strlen(tilde_position) + 1);
	if (!string)
		return (start);
	ft_strlcpy(string, start, tilde_position - start + 1);
	ft_strlcpy(string + ft_strlen(string), expansion, 
				ft_strlen(expansion) + 1);
	ft_strlcpy(string + ft_strlen(string), tilde_position + 1, 
				ft_strlen(tilde_position));
	free(start);
	free(expansion);
	return (string);
}

char	*tilde_expansion(char *input, t_env **env)
{
	char	*current;

	if (!input)
		return (NULL);
	current = input;
	while (*current)
	{
		if (*current == '\'' || *current == '"')
			current = ft_strchr(current + 1, *current);
		if (*current == '~')
		{
			if (ft_check_before_tilde(&current[-1], input)
				&& ft_check_after_tilde(&current[1]))
				return (make_string(input, current, env, 0));
			else
				break;
		}
		current++;
	}
	return (input);
}
