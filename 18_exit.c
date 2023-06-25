/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:13:25 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/25 16:06:52 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

long	ft_atoll(char *s)
{
	long	numb;
	int		sign;

	if (!s)
		return (0);
	numb = 0;
	while (ft_isspace(*s))
		s++;
	sign = (*s == '+' || ft_isdigit(*s)) - (*s == '-');
	s += (*s == '+' || *s == '-');
	while (ft_isdigit(*s))
		numb = numb * 10 + *s++ - '0';
	return (numb * sign);
}

int	numb_fits_max_long(char *numb_begin, int sign)
{
	int		index;
	char	*big_long;

	if (sign == 1)
		big_long = "9223372036854775807";
	else
		big_long = "9223372036854775808";
	index = 0;
	while (big_long[index] && numb_begin[index] == big_long[index])
		index++;
	if (big_long[index] && numb_begin[index] > big_long[index])
		return (0);
	return (1);
}

int	is_valid_number(char *s)
{
	char	*numb_begin;
	int		len;
	int		sign;

	if (!s)
		return (1);
	while (ft_isspace(*s))
		s++;
	len = 0;
	sign = (*s == '+' || ft_isdigit(*s)) - (*s == '-');
	s += (*s == '+' || *s == '-');
	while (*s == '0')
		s++;
	numb_begin = s;
	while (ft_isdigit(*s))
	{
		if (++len > 19)
			return (0);
		s++;
	}
	while (*s == ' ' || *s == '\t')
		s++;
	if (len == 19 && numb_fits_max_long(numb_begin, sign) == 0)
		return (0);
	return (!*s && s > numb_begin);
}

void	print_exit_error(char *argument)
{
	char	*message;

	message = ft_strjoin("exit: ", argument);
	if (!message)
		message = "exit error Σ(O_O)";
	print_error(message, "Numeric argument required ─=≡Σ((( つ＞＜)つ", 2);
	if (ft_strncmp(message, "exit ", 5))
		free(message);
}

int	ft_exit(char **command, t_redirects redir, t_env **env, int exit_status)
{
	long	num;

	if (!command || !command[1])
		num = 0;
	else if (is_valid_number(command[1]) && command[2] != NULL)
		return (print_error(command[0], "Too many arguments （´○｀）～ゝ", 1));
	else if (is_valid_number(command[1]))
		num = ft_atoll(command[1]);
	else
	{
		print_exit_error(command[1]);
		num = 2;
	}
	free_matrix(command);
	free_list(env);
	close(redir.fd_input);
	close(redir.fd_output);
	rl_clear_history();
	exit(num);
	(void)env;
	(void)exit_status;
}
