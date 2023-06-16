/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:48:51 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/16 20:19:21 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*match;

	match = NULL;
	while (*s)
	{
		if (*s++ == (unsigned char)c)
			match = (char *)s - 1;
	}
	if (*s == c)
		return ((char *)s);
	return (match);
}
