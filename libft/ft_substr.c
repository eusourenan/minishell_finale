/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:27:58 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/14 23:24:15 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!s || !*s || !(start < s_len && len > 0))
		return (ft_strdup(""));
	if (len >= s_len)
		sub = (char *)malloc((s_len - start + 1) * sizeof(char));
	else
		sub = (char *)malloc(len + 1);
	s += start;
	start = 0;
	while (len-- > 0 && s[start])
	{
		sub[start] = s[start];
		start++;
	}
	sub[start] = 0;
	return (sub);
}
