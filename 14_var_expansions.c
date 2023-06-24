/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_var_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:13:05 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/24 15:17:54 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

char	*find_var(char *input)
{
	char	*start;

	start = input;
	while (input && *input)
	{
		if (-*input > 0 && *input == -1)
			while (*(++input) != -1)
				;
		else if (-*input > 0 && *input == -2)
		{
			while (*++input != -2)
				if (*input == '$' && \
				(ft_isalpha(input[1]) || input[1] == '_' || input[1] == '?'))
					return (input + 1);
		}
		else if (*input == '$'
			&& (ft_isalpha(input[1]) || input[1] == '_' || input[1] == '?'))
			if (start + 3 > input || input[-2] != '<' || input[-3] != '<')
				return (input + 1);
		if (input)
			input++;
	}
	return (NULL);
}

char	*get_var_name(char *start)
{
	char	*name;
	char	*end;

	if (!start)
		return (NULL);
	end = start;
	if (*end == '?')
		end++;
	else if (ft_isalpha(*end) || *end == '_')
		while (ft_isalnum(*end) || *end == '_')
			end++;
	name = ft_substr(start, 0, end - start);
	if (!name)
		return (NULL);
	return (name);
}

char	*get_value_of_var(char *var, t_env **env, int exit_status)
{
	t_env	*aux;

	aux = *env;
	if (var && *var == '?')
		return (ft_itoa(exit_status));
	while (aux)
	{
		if (ft_strncmp(aux->var, var, ft_strlen(var) + 1) == '=')
			return (ft_strdup(aux->var + ft_strlen(var) + 1));
		aux = aux->next;
	}
	return (NULL);
}

char	*expand_variables(char *input, t_env **env, int exit_status)
{
	char	*var_start;
	char	*var_name;
	char	*value;
	char	*temp;

	var_start = find_var(input);
	if (!var_start)
		return (input);
	var_name = get_var_name(var_start);
	if (!var_name)
		return (input);
	value = get_value_of_var(var_name, env, exit_status);
	temp = malloc(var_start - input + (!value) +\
		ft_strlen(value) + (ft_strlen(var_start) - ft_strlen(var_name)));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, input, var_start - input);
	ft_strlcpy(temp + ft_strlen(temp), value, ft_strlen(value) + 1);
	ft_strlcpy(temp + ft_strlen(temp), var_start + ft_strlen(var_name), \
			ft_strlen(var_start + ft_strlen(var_name)) + 1);
	free(value);
	free(input);
	free(var_name);
	input = temp;
	return (expand_variables(input, env, exit_status));
}
