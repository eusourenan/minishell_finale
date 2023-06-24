/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:13:21 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/24 15:18:25 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	*set_builtin(char **command)
{
	if (!command || !*command || !**command)
		return (NULL);
	if (!ft_strncmp(command[0], "echo", 5))
		return (ft_echo);
	if (!ft_strncmp(command[0], "cd", 3))
		return (ft_cd);
	if (!ft_strncmp(command[0], "pwd", 4))
		return (ft_pwd);
	if (!ft_strncmp(command[0], "export", 7))
		return (ft_export);
	if (!ft_strncmp(command[0], "unset", 6))
		return (ft_unset);
	if (!ft_strncmp(command[0], "env", 4))
		return (ft_env);
	if (!ft_strncmp(command[0], "exit", 5))
		return (ft_exit);
	if (!ft_strncmp(command[0], "help", 5))
		return (ft_help);
	return (NULL);
}

int	ft_help(char **command, t_redirects redir, t_env **env, int exit_status)
{
	char	*message;

	message = "This is the help message\nYour life will NEVER be the same.\n"\
	"\nLook how I shine: °˖✧◝(⁰▿⁰)◜✧˖°\nThis is a MINISHELL and it's COMPLETE"\
	": o(≧▽≦)o\n\nWas hard to code me, people used to (」＞＜)」o(>< )o 凸(￣ヘ￣)"\
	"  while coding me.\nPissed off too. Just like that: ٩(╬ʘ益ʘ╬)۶\nAnd cried"\
	" a lot! (｡•́︿•̀｡) (っ˘̩╭╮˘̩)っ ｡･ﾟﾟ*(>д<)*ﾟﾟ･｡ (×_×)\n\nBut, in the end:"\
	"\nThe real minishell is the friends we made along the way ヽ( ⌒o⌒)人"\
	"(⌒-⌒ )ﾉ o(^^o)(o^^o)(o^^o)(o^^)o ＼(▽￣ \\ (￣▽￣) / ￣▽)／\n";
	ft_putendl_fd(message, redir.fd_output);
	return ((command != 0) * 0);
	(void)exit_status;
	(void)env;
}

int	ft_echo(char **command, t_redirects redir, t_env **env, int exit_status)
{
	char	*line_feed;

	if (!command)
		return (ENOMEM);
	line_feed = command[1];
	if (line_feed && *line_feed == '-')
		line_feed++;
	while (line_feed && *line_feed && *line_feed == 'n')
		line_feed++;
	exit_status = (line_feed > command[1] + 1 && line_feed[-1] == 'n');
	if (line_feed && !*line_feed && line_feed > command[1] + 1)
		command = command + 2;
	else
		command = command + 1;
	while (*command)
	{
		ft_putstr_fd(*command++, redir.fd_output);
		if (*command)
			ft_putstr_fd(" ", redir.fd_output);
	}
	if (!(line_feed && !*line_feed && exit_status))
		write(redir.fd_output, "\n", 1);
	return (0);
	(void)env;
}

int	ft_pwd(char **command, t_redirects redir, t_env **env, int exit_status)
{
	char	*pwd;

	if (!command)
		return (12);
	pwd = getcwd(0, 0);
	if (!pwd)
		return (print_format_error("Buffer is NULL. ┐(￣ヘ￣;)┌", 12));
	if (ft_strlen(pwd) > 4096)
		ft_putendl_fd("File name id too long! (＠_＠)", 2);
	ft_putendl_fd(pwd, redir.fd_output);
	if (command[1])
		print_format_error("ignoring the rest, man! (ーー;)\n", 2);
	free(pwd);
	return (0);
	(void)(env);
	(void)(exit_status);
}

int	ft_env(char **command, t_redirects redir, t_env **env, int exit_status)
{
	char	*error_message;
	t_env	*aux;

	if (!command)
		return (0);
	if (command[1] != NULL)
	{
		error_message = "YOU JUST HAVE ONE JOB! Read The F*@# PDF!!!"\
		"⸨◣_◢⸩\nHe explicit says that we DON'T have to implement env with"\
		" some options or arguments. Respect that!\nGODAMIT!!!┌∩┐(◣_◢)┌∩┐\n\n"\
		"Have a nice day! (｡^‿^｡) ٩(◕‿◕)۶\n";
		print_format_error(error_message, 2);
		return (2);
	}
	aux = *env;
	while (aux)
	{
		if (ft_strchr(aux->var, '='))
			ft_putendl_fd(aux->var, redir.fd_output);
		aux = aux->next;
	}
	return (0);
	(void)exit_status;
}
