/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:11:22 by rleite-s          #+#    #+#             */
/*   Updated: 2023/06/15 18:49:02 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static char	*ft_insert_str(char const *s, int start, char c)
{
	int		size;
	int		index;
	char	*str;

	size = 0;
	s += start;
	while (*s != c && *s)
	{
		size++;
		s++;
	}
	str = (char *)malloc(size + 1);
	str[size] = '\0';
	index = 0;
	s -= size;
	while (index < size)
		str[index++] = *s++;
	return (str);
}

static int	*ft_count_lines(char const *s, char c, int *positions)
{
	size_t	lines;
	size_t	index;
	size_t	s_len;

	s_len = ft_strlen(s);
	index = 0;
	lines = 0;
	if (s_len)
		positions = ((int *)malloc(((s_len / 2) + 1) * sizeof(int)));
	else
		positions = ((int *)malloc(2 * sizeof(int)));
	while (s[index] == c && s[index])
		index++;
	if (index != s_len)
		positions[++lines] = index;
	while (s[index])
	{
		if (s[index] == c && s[index + 1] != c && s[index + 1])
			positions[++lines] = index + 1;
		index++;
	}
	positions[lines + 1] = -1;
	positions[0] = lines;
	return (positions);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		*positions;
	int		index;

	split = NULL;
	positions = NULL;
	positions = ft_count_lines(s, c, positions);
	split = (char **)malloc((positions[0] + 1) * sizeof(char *));
	index = 1;
	while (positions[index] != -1)
	{
		split[index - 1] = ft_insert_str(s, positions[index], c);
		index++;
	}
	split[index - 1] = NULL;
	free(positions);
	return (split);
}*/

int	count_words(const char *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (!*s)
			break;
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
			break;
		end = (char *)s;
		while (*end != c && *end)
			end++;
		splited[words++] = ft_substr(s, 0, end - s);
		while (*s != c && *s)
			s++;
	}
	return (splited);
}
/*#include <stdio.h>
int	main()
{
	char	**splitted = 
	ft_split("/nfs/homes/rleite-s/bin:/nfs/homes/rleite-s/bin:/usr/local/sbin:"\
	"/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"
	, ':');
	char **tmp;
	if (!splitted)
	{
		puts("Deu ruim!");
		return (1);
	}
	tmp = splitted;
	while (*splitted)
	{
		ft_putendl_fd(*splitted, 1);
		free(*splitted++);
	}
	free(tmp);
}*/