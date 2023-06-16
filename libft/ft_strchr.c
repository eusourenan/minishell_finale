/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 01:53:50 by rleite-s          #+#    #+#             */
/*   Updated: 2023/06/15 18:11:49 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (s && *s)
		if (*s++ == (unsigned char)c)
			return ((char *)--s);
	if (s && *s == c)
		return ((char *)s);
	return (NULL);
}
