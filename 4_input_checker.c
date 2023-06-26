/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_input_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:10:57 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/26 14:06:59 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	has_input_error(char *input)
{
	if (!input || !*input)
		return (1);
	add_history(input);
	find_comment(input);
	if (ft_is_only_spaces(input))
		return (1);
	ft_adjust_delimiters(input);
	if (ft_has_invalid_pipe(input))
		return (1);
	if (has_unclosed_quotes(input))
		return (1);
	if (has_redirect_error(input))
		return (1);
	return (0);
}

int	ft_is_only_spaces(char *input)
{
	if (input == NULL)
		return (1);
	if (!*input)
		return (0);
	while (*input)
	{
		if (ft_isspace(*input) == 1)
			input++;
		else
			return (0);
	}
	return (1);
}

int	ft_has_invalid_pipe(char *input)
{
	if (input == NULL)
		return (1);
	if (input && *input == '|')
		return (1);
	while (input && *input)
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		if (input && *input == '|')
		{
			input++;
			if (!*input || *input == '|' || (*input && input[1] == '|'))
				return (1);
		}
		else if (input)
			input++;
	}
	return (0);
}

int	has_unclosed_quotes(char *input)
{
	if (input == NULL)
		return (1);
	while (*input != '\0')
	{
		if (*input == '\'')
		{
			input = ft_strchr(input + 1, '\'');
			if (input == NULL)
				return (1);
		}
		else if (*input == '"')
		{
			input = ft_strchr(input + 1, '"');
			if (input == NULL)
				return (1);
		}
		input++;
	}
	return (0);
}

int	has_redirect_error(char *input)
{
	if (input == NULL)
		return (1);
	while (*input)
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		if (*input == '<' || *input == '>')
		{
			input++;
			if (*input == '<' || *input == '>')
			{
				if (*input != input[-1])
					return (1);
				if (input[1] == '<' || input[1] == '>' || !input[1])
					return (1);
				if (input[1] == 32 && (input[2] == 60 || input[2] == 62
						|| input[2] == '|'))
					return (1);
			}
			if (*input == '|' || !*input)
				return (1);
		}
		input++;
	}
	return (0);
}
