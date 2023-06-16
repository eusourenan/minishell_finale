/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 02:40:26 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/14 23:22:44 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short int	ft_is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;
	size_t	index;

	start = 0;
	end = ft_strlen(s1) - 1;
	index = 0;
	while (ft_is_in_set(s1[start], set))
		start++;
	while (end > start && ft_is_in_set(s1[end], set))
		end--;
	if (++end > start)
		trim = (char *)malloc(end - start + 1);
	else
		trim = (char *)malloc(1);
	if (trim == NULL)
		return (NULL);
	while (start < end)
		trim[index++] = s1[start++];
	trim[index] = 0;
	return (trim);
}
