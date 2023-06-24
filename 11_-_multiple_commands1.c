#include "minishell.h" 

int	close_heredocs_except_in_index(int *heredocs, int index_to_save)
{
	int	index;

	index = 0;
	while (heredocs[index] != -2)
	{
		if (index != index_to_save && heredocs[index] != -1)
			close(heredocs[index]);
		index++;
	}
	return (heredocs[index_to_save]);
}

int	free_commands_and_heredocs(char **commands, int *heredocs, int exit_status)
{
	free_matrix(commands);
	free(heredocs);
	return (WEXITSTATUS(exit_status));
}

void	finishing_command(t_env **env, int exit_status)
{
	free_list(env);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(exit_status);
}

void	parent_fds_control
(int pipes[], int *bkp_input, char **commands, int actual_command)
{
	ft_close(*bkp_input, STDIN_FILENO);
	if (commands[actual_command + 1])
	{
		*bkp_input = dup(pipes[0]);
		close(pipes[0]);
		close(pipes[1]);
	}
	else
		close(*bkp_input);
}

void	wait_all_childs(int *fork_pids, int *exit_status)
{
	int	index;

	index = 0;
	while (fork_pids[index])
		waitpid(fork_pids[index++], exit_status, 0);
}

