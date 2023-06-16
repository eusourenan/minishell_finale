/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 03:12:21 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/23 21:53:12 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	index;

	if (size > ft_strlen(dst))
		dst_len = ft_strlen(dst);
	else
		dst_len = size;
	index = 0;
	if (size > dst_len)
	{
		while (index < (size - dst_len - 1) && src[index])
		{	
			dst[dst_len + index] = src[index];
			index++;
		}
		dst[dst_len + index] = '\0';
	}
	return (dst_len + ft_strlen(src));
}
