/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:11:22 by rleite-s          #+#    #+#             */
/*   Updated: 2023/06/24 15:05:08 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (!*s)
			break ;
		words++;
		while (*s != c && *s)
			s++;
	}
	return (words);
}

char	**ft_split(const char *s, char c)
{
	char	**splited;
	char	*end;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	splited = (char **)ft_calloc((words + 1), sizeof(char *));
	words = 0;
	if (!splited)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (!*s)
			break ;
		end = (char *)s;
		while (*end != c && *end)
			end++;
		splited[words++] = ft_substr(s, 0, end - s);
		while (*s != c && *s)
			s++;
	}
	return (splited);
}
