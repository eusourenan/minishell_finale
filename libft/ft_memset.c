/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:31:08 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/14 23:36:39 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = (unsigned char)c;
	return (s);
}

/* int	main(void)
{
	char	*tes = "TESTE";
	int		size = 3;

	tes = (char *) malloc(6);
	printf("Original: %s\n", (char *)memset(tes, 1580, size));
	printf("Minha Result: %s\n", (char *)ft_memset(tes, 1580, size));
	return (0);
} */
