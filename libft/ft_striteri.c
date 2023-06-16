/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:22:35 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/14 22:48:18 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* void	ft_striteri(char *s, void (*f) (unsigned int, char *))
{
	unsigned int	index;

	index = 0;
	while (s[index])
	{
		f(index, &s[index]);
		index++;
	}
} */

void	ft_striteri(char *s, void (*f) (unsigned int, char *))
{
	unsigned int	index;

	index = 0;
	while (*s)
		f(index++, s++);
}
