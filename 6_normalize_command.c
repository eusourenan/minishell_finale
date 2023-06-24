/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_normalize_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:11:24 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/24 15:16:06 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	normalize_command(char *input, t_env **env, int exit_status)
{
	char	**commands;
	int		*heredocs;
	int		qtd_commands;

	input = redirect(input);
	if (input)
		input = put_minus_five_after_redirects(input);
	if (!input)
		return (12);
	commands = split_commands(input);
	free(input);
	if (!commands)
		return (12);
	qtd_commands = count_commands(commands);
	heredocs = ft_calloc(qtd_commands + 1, sizeof(int));
	if (!heredocs)
	{
		free_matrix(commands);
		return (12);
	}
	heredocs[qtd_commands] = -2;
	return (set_heredocs_and_execute(commands, env, exit_status, heredocs));
}

int	number_of_redirects(char *str)
{
	int		i;
	int		count;
	char	*quote_address;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote_address = ft_strchr(&str[i + 1], str[i]);
			if (!quote_address)
				return (-1);
			i += quote_address - &str[i];
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			count++;
			if (str[i] == str[i + 1])
				i++;
		}
		i++;
	}
	return (count);
}

char	*redirect(char *str)
{
	char	*start;
	char	*newstr;
	char	*new_aux;

	start = str;
	newstr = ft_calloc(1, ft_strlen(str) + number_of_redirects(str) + 1);
	if (!newstr)
		return (NULL);
	new_aux = newstr;
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '"')
		{
			ft_strlcpy(newstr, str, ft_strchr(str + 1, *str) - str + 1);
			str += ft_strlen(newstr);
			newstr += ft_strlen(newstr);
		}
		else if (*str == '<' || *str == '>')
			if (str > start && ((str[-1] != ' ' && str[1] == *str) || \
				(str[-1] != *str)))
				*newstr++ = ' ';
		*newstr++ = *str++;
	}
	free(start);
	return (new_aux);
}

char	*put_minus_five_after_redirects(char *str)
{
	char	*start;
	char	*newstr;
	char	*new_aux;

	start = str;
	newstr = ft_calloc(1, ft_strlen(str) + number_of_redirects(str) + 1);
	if (!newstr)
		return (NULL);
	new_aux = newstr;
	while (*str)
	{
		*newstr = *str;
		if (str > start && (((str[-1] == '<' || str[-1] == '>') && str[1] && \
		(*str != '<' && *str != '>') && (*str != ' ' || *str++ == ' '))))
			*newstr++ = -5;
		if (*str == '\'' || *str == '"')
		{
			ft_strlcpy(newstr, str, ft_strchr(str + 1, *str) - str + 2);
			str += ft_strlen(newstr) - 1;
			newstr += ft_strlen(newstr) - 1;
		}
		*newstr++ = *str++;
	}
	free(start);
	return (new_aux);
}

int	count_commands(char **cmd)
{
	int	count;

	count = 0;
	if (!cmd)
		return (0);
	while (cmd[count])
		count++;
	return (count);
}
