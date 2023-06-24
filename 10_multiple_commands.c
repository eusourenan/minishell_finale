/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_multiple_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:10:01 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/24 15:17:07 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	prepare_multiple_commands(char **commands, t_env **env, int exit_s, \
						int *heredocs)
{
	int		pipes[2];
	int		bkp_input;
	t_vars	cmd;
	int		fd_hdoc;
	int		actual;

	bkp_input = 0;
	actual = 0;
	if (start_fork_pids(commands, &cmd))
		return (12);
	while (commands[actual])
	{
		start_pipes(commands, pipes, &cmd, actual);
		if (cmd.heredocs[actual] == 0)
		{
			cmd.commands = commands;
			initial_adjust_of_commands(pipes, bkp_input, &cmd, actual);
			fd_hdoc = pre_execution(commands, &cmd, heredocs, actual);
			exit_s = execute_one_command(cmd.commands, env, exit_s, fd_hdoc);
			finishing_command(env, exit_s);
		}
		parent_fds_control(pipes, &bkp_input, commands, actual++);
	}
	wait_all_childs(cmd.heredocs, &exit_s);
	return (free_commands_and_heredocs(commands, cmd.heredocs, exit_s));
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

void	initial_adjust_of_commands(int pipes[], int bkp_input, \
						t_vars *command, int actual_command)
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
