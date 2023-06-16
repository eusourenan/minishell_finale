

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <err.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <bsd/string.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft.h"

struct s_env
{
	char			*var;
	struct s_env	*next;
};

typedef struct s_env	t_env;

struct s_redirects
{
	t_env	*redirects;
	int		fd_heredoc;
	int		fd_input;
	int		fd_output;
};

typedef struct s_redirects t_redirects;

// env.c
char	**list_to_pointer(t_env *list);
t_env	*pointer_to_list(char **envp);

// list.c
void	free_list(t_env **list);
void	add_back(t_env **list, t_env *node);
t_env	*new_node(char *value);
size_t	list_size(t_env *list);

// main.c


#endif