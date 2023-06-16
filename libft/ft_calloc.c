/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 01:54:29 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/14 22:40:39 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*alloc;
	int		over;

	over = nmemb * size;
	if (over == 0 || over / nmemb != size)
		return (NULL);
	alloc = (void *) malloc(over);
	if (alloc == NULL)
		return (NULL);
	ft_bzero(alloc, over);
	return (alloc);
}
