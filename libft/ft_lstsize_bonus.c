/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 19:00:11 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/17 23:04:26 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 1;
	while (lst->next)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

/* int main(void)
{
	t_list *novo = ft_lstnew("Primeira mensagem");
	// *novo = teste;
	printf("1 - %d \n", ft_lstsize(novo));
	ft_lstadd_front(&novo, ft_lstnew("Segunda mensagem"));
	printf("2 - %d \n", ft_lstsize(novo));
	ft_lstadd_front(&novo, ft_lstnew("Terceira"));
	
	printf("Tamanho da lista: %d\n", ft_lstsize(novo));
	
	return (0);
}  */