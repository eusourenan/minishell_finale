/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:25:40 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/15 00:20:21 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*dup;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	dup = (char *) malloc(++size * sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (size--)
		dup[size] = s[size];
	return (dup);
}
