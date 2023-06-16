/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 02:22:13 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/24 18:53:19 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*index;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = (char *)ft_calloc(s1_len + s2_len + 1, 1);
	if (join == NULL)
		return (NULL);
	index = join;
	ft_memcpy(index, s1, s1_len);
	index += ft_strlen(s1);
	ft_memcpy(index, s2, s2_len);
	return ((char *)join);
}
