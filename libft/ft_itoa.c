/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:46:40 by rleite-s          #+#    #+#             */
/*   Updated: 2022/07/09 00:01:39 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	ft_rev_numb(char *str)
{
	size_t	len;
	size_t	index;
	char	swap;

	index = 0;
	len = ft_strlen(str) - 1;
	while (index < len)
	{
		swap = *(str + index);
		*(str + index++) = *(str + len);
		*(str + len--) = swap;
	}
}

static char	*ft_make_str(int n, int digits)
{
	char	*str;

	if (n < -9 || n > 9)
		str = ft_make_str(n / 10, digits + 1);
	else
	{
		str = (char *)malloc(digits + 1 + (n < 0));
		if (n < 0)
			str[0] = '-';
		str[digits + (n < 0)] = '\0';
	}
	str[--digits + (n < 0)] = ft_abs(n % 10) + '0';
	if (!digits)
		ft_rev_numb(str + (n < 0));
	return (str);
}

char	*ft_itoa(int n)
{
	return (ft_make_str(n, 1));
}
