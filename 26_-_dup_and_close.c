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
