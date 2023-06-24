#include "minishell.h" 

int	prepare_multiple_commands
(char **commands, t_env **env, int exit_status, int *heredocs)
{
	int		pipes[2];
	int		bkp_input;
	t_vars	command;
	int		fd_heredoc;
	int		actual;

	bkp_input = 0;
	actual = 0;
	if (start_fork_pids(commands, &command))
		return (12);
	while (commands[actual])
	{
		start_pipes(commands, pipes, &command, actual);
		if (command.heredocs[actual] == 0)
		{
			command.commands = commands;
			initial_adjust_of_commands(pipes, bkp_input, &command, actual);
			fd_heredoc = pre_execution(commands, &command, heredocs, actual);
			exit_status = execute_one_command(command.commands, env, exit_status, fd_heredoc);
			finishing_command(env, exit_status);
		}
		parent_fds_control(pipes, &bkp_input, commands, actual++);
	}
	wait_all_childs(command.heredocs, &exit_status);
	return (free_commands_and_heredocs(commands, command.heredocs, exit_status));
}

int	start_fork_pids(char **commands, t_vars *command)
{
	command->heredocs = ft_calloc(count_commands(commands) + 1, sizeof(int));
	if (!command->heredocs)
	{
		free_matrix(commands);
		return (12);
	}
	return (0);
}

void	start_pipes(char **commands, int pipes[], t_vars *command, int actual)
{
	if (commands[actual + 1])
		pipe(pipes);
	command->heredocs[actual] = fork();
	execution_signals(command->heredocs[actual]);
}

void	initial_adjust_of_commands
(int pipes[], int bkp_input, t_vars *command, int actual_command)
{
	rl_clear_history();
	free(command->heredocs);
	if (command->commands[actual_command + 1])
		close(pipes[0]);
	ft_dup2(bkp_input, STDIN_FILENO);
	if (command->commands[actual_command + 1])
		ft_dup2(pipes[1], STDOUT_FILENO);
}

int	pre_execution(char **commands, t_vars *command, int *heredocs, int actual)
{
	int	fd_heredoc;

	command->commands = split_commands(commands[actual]);
	fd_heredoc = close_heredocs_except_in_index(heredocs, actual);
	free_commands_and_heredocs(commands, heredocs, 0);
	return (fd_heredoc);
}
