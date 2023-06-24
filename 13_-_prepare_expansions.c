#include "minishell.h" 

int	expand_all(char **commands, t_env **env, int exit_status)
{
	char	*expanded;
	int		var;

	while (commands && *commands)
	{
		var = 0;
		if (**commands == '$')
			var = 1;
		expanded = make_expansions_and_remove_quotes\
					(*commands, env, exit_status);
		if (!expanded)
			return (12);
		if (expanded != *commands && !*expanded && var)
		{
			free(expanded);
			adjust_commands(commands);
		}
		else if (expanded != *commands)
			*commands++ = expanded;
		else
			commands++;
	}
	return (0);
}

char	*make_expansions_and_remove_quotes
(char *input, t_env **env, int exit_status)
{
	char	*temp;

	if (input)
	{
		input = tilde_expansion(input, env);
		ft_modify_quotemarks_to_remove(input, "'\"");
		temp = input;
		input = expand_variables(input, env, exit_status); 
		if (!input)
		{
			free(temp);
			return (NULL);
		}
		ft_removing_modified_quotemarks(input, "'\"");
	}
	return (input);
}

void	ft_modify_quotemarks_to_remove(char *input, char *set)
{
	char	quote;
	int		index;

	while (input && *input)
	{
		if (ft_is_in_set(*input, set))
		{
			quote = *input;
			index = get_index(quote, set);
			if (index != -1)
				*input = (-index) - 1;
			input = ft_strchr(input, quote);
			index = get_index(quote, set);
			if (index != -1)
				*input = (-index) - 1;
		}
		input++;
	}
}

int	get_index(char c, char *s)
{
	int	index = 0;

	while(s && s[index])
	{
		if (c == s[index])
			return (index);
		index++;
	}
	return (-1);
}

void	ft_removing_modified_quotemarks(char *input, char *set)
{
	while (input && *input)
	{
		if (-*input > 0 && -(*input) <= (int)ft_strlen(set))
			ft_memmove(input, input + 1, ft_strlen(input));
		else if (*input)
			input++;
	}
}
