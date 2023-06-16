/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:41:12 by rleite-s          #+#    #+#             */
/*   Updated: 2022/07/05 19:40:46 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char			*mapi;
	unsigned int	index;

	mapi = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (mapi == NULL)
		return (NULL);
	index = 0;
	while (s && f && s[index])
	{
		mapi[index] = f(index, s[index]);
		index++;
	}
	mapi[index] = 0;
	return (mapi);
}
