/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 01:29:09 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/18 02:25:53 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcmp(const char *little, const char *big, size_t n)
{
	while (*little && n-- && *little == *big)
	{
		little++;
		big++;
	}
	return ((unsigned char)*little);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l_len;

	l_len = ft_strlen(little);
	if (!l_len)
		return ((char *)big);
	while (len-- >= l_len && *big)
	{
		if (ft_strcmp(little, big, l_len))
			big++;
		else
			return ((char *)big);
	}
	return (NULL);
}
