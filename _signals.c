#include "minishell.h" 

void	init_signals(void)
{
	signal(SIGINT, redo_readline);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

void	redo_readline(int signal)
{
	if (signal == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	heredoc_signals(int pid)
{
	if (pid == 0)
		signal(SIGINT, free_heredoc);
	else
		signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	free_heredoc(int signal)
{
	if (signal == SIGINT)
		set_and_free_heredoc(0, 0, 0);
}

void	execution_signals(int pid)
{
	if (pid == 0)
		signal(SIGINT, SIG_DFL);
	else
		signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
