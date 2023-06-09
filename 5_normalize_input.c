/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_normalize_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:11:17 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/25 04:56:43 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	find_comment(char *input)
{
	char	*start;

	start = input;
	while (input && *input)
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		if (input && *input == '#')
		{
			if (input == start || ft_isspace(input[-1]))
			{
				*input = 0;
				return ;
			}
		}
		if (input)
			input++;
	}
}

void	ft_adjust_delimiters(char *s)
{
	char	*end;

	end = s;
	while (end && ft_isspace(*end))
		end++;
	if (end && end != s)
		ft_memmove(s, end, ft_strlen(end) + 1);
	while (s && *s)
	{
		if (*s == '\'' || *s == '"')
			s = ft_strchr(s + 1, *s);
		if (s && ft_isspace(*s))
		{
			end = s + 1;
			while (ft_isspace(*end))
				end++;
			*s = ' ' * (*end != '\0');
			if (s + 1 != end)
				ft_memmove(s + 1, end, ft_strlen(end) + 1);
		}
		if (s)
			s++;
	}
}
