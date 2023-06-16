/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:41:41 by rleite-s          #+#    #+#             */
/*   Updated: 2022/06/17 22:06:12 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*actual;

	map = NULL;
	while (lst)
	{
		actual = ft_lstnew(f(lst->content));
		if (!actual)
			ft_lstdelone(actual, del);
		else
			ft_lstadd_back(&map, actual);
		lst = lst->next;
	}
	return (map);
}
