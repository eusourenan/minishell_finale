
#include "minishell.h"

void	set_shlvl(char **envp)
{
	int		level;
	char	*char_level;
	char	*join;

	while (envp && *envp)
	{
		if (strncmp(*envp, "SHLVL", 6) == '=')
			break;
		envp++;
	}
	if (*envp)
	{
		level = ft_atoi(*envp + 6);
		char_level = ft_itoa(level + 1);
		if (!char_level)
			return ;
		join = ft_strjoin("SHLVL=", char_level);
		free(char_level);
		if (!join)
			return ;
		*envp = join;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*list;
	int		ret;

	if (argc > 1 || argv[1])
	{
		ft_putendl_fd("EXECUTE ME PROPERLY, YOU ASSHOLE!!! ┗|｀O′|┛", 2);
		return (2);
	}
	set_shlvl(envp);
	list = pointer_to_list(envp);
	if (!list)
	{
		ft_putendl_fd("You don't have space, bro! (っ˘̩╭╮˘̩)っ", 2);
		return (ENOMEM);
	}
	ret = minishell(&list);
	free_list(&list);
	rl_clear_history();
	ft_putendl_fd("exit", 1);
	return (ret);
}
