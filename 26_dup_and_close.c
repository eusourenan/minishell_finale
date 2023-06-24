/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   26_dup_and_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:14:07 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/24 15:22:47 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	ft_dup2(int new, int old)
{
	if (new != old)
	{
		dup2(new, old);
		close(new);
	}
}

void	ft_close(int fd, int check)
{
	if (fd < 0)
		return ;
	if (fd != check)
		close(fd);
}
