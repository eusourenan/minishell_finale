/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:58:55 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/17 22:04:52 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Recursivo
/* void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	if (!lst)
		return;
	if (*lst)
		ft_lstclear(&(*lst)->next, del);
	ft_lstdelone(*lst, del);
	lst = NULL;
} */

// Iterativo
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
	*lst = NULL;
}
