/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_print_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:13:56 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/24 15:22:45 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	print_format_error(char *message, int exit_status)
{
	write(2, message, ft_strlen(message));
	return (exit_status);
}

int	print_error(char *command, char *error, int exit_status)
{
	char	*message;
	char	*aux;

	message = ft_strjoin("minishell: ", command);
	if (!message)
		return (print_format_error("No more memory ¯\\_| ✖ 〜 ✖ |_/¯\n", 12));
	aux = ft_strjoin(message, " : ");
	free(message);
	if (!aux)
		return (print_format_error("No more memory ¯\\_▐ ☯ ︿ ☯ ▐_/¯\n", 12));
	message = ft_strjoin(aux, error);
	free(aux);
	if (!message)
		return (print_format_error("No more memory ¯\\_(☯෴☯)_/¯\n", 12));
	aux = message;
	message = ft_strjoin(message, ", dude! (っ´ω`)ﾉ(╥ω╥)\n");
	free(aux);
	if (!message)
		return (print_format_error("No more memory ( ◡‿◡ *)\n", 12));
	exit_status = print_format_error(message, exit_status);
	free(message);
	return (exit_status);
}

int	print_file_error(char *path, int code)
{
	if (code == 125)
		return (print_error(path, "Is a directory 凸(￣ヘ￣)", 126));
	if (code == 126)
		return (print_error(path, "Permission denied (；⌣̀_⌣́)", 126));
	if (code == 127)
		return (print_error(path, "No such file/directory (￣ ￣|||)", 127));
	return (0);
}

int	print_arg_error(char *command, char *arg, char *error, int exit_status)
{
	char	*message;

	message = ft_strjoin("`", arg);
	if (!message)
		return (print_format_error("No more memory\n", 12));
	arg = ft_strjoin(message, ": ");
	free(message);
	if (!arg)
		return (print_format_error("No more memory\n", 12));
	message = ft_strjoin(arg, error);
	free(arg);
	if (!message)
		return (print_format_error("No more memory\n", 12));
	exit_status = print_error(command, message, exit_status);
	free(message);
	return (exit_status);
}
