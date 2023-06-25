/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:13:44 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/06/25 01:52:58 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	new_old_pwd(t_env *pwd, t_env *old_pwd, t_env **env)
{
	char	*var_old_pwd;

	if (pwd)
	{
		var_old_pwd = ft_strjoin("OLD", pwd->var);
		if (!var_old_pwd)
			return (12);
		if (old_pwd)
		{
			free(old_pwd->var);
			old_pwd->var = var_old_pwd;
		}
		else
		{
			old_pwd = ft_calloc(sizeof(t_env), 1);
			if (!old_pwd)
			{
				free(var_old_pwd);
				return (12);
			}
			old_pwd->var = var_old_pwd;
			add_back(env, old_pwd);
		}
	}
	return (0);
}

int	new_pwd(char *cwd, t_env *pwd, t_env *old_pwd, t_env **env)
{
	char	*new_pwd;

	new_old_pwd(pwd, old_pwd, env);
	if (pwd)
	{
		new_pwd = ft_strjoin("PWD=", cwd);
		if (!new_pwd)
			return (12);
		free(pwd->var);
		pwd->var = new_pwd;
	}
	else
	{
		pwd = ft_calloc(sizeof(t_env), 1);
		if (!pwd)
			return (12);
		pwd->var = ft_strjoin("PWD=", cwd);
		if (!pwd->var)
		{
			free(pwd);
			return (12);
		}
		add_back(env, pwd);
	}
	return (0);
}

int	update_pwds(t_env **env)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*cwd;

	pwd = var_is_in_list("PWD", env);
	old_pwd = var_is_in_list("OLDPWD", env);
	if (!pwd && !old_pwd)
		return (0);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (12);
	new_pwd(cwd, pwd, old_pwd, env);
	free(cwd);
	return (0);
}

char	*get_path(char *arg, t_env **env)
{
	char	*path;
	t_env	*old_pwd;

	if (*arg == '-' && !arg[1])
	{
		old_pwd = var_is_in_list("OLDPWD", env);
		if (!old_pwd)
		{
			print_error("cd", "OLDPWD not set", 0);
			return (NULL);
		}
		path = ft_strdup(old_pwd->var + 7);
		if (!path)
			return (NULL);
	}
	else
		path = arg;
	return (path);
}

int	ft_cd(char **cmd, t_redirects redir, t_env **env, int exit_status)
{
	char	*path;

	if (!cmd)
		return (12);
	if (!cmd[1] || (cmd[1][0] == '-' && cmd[1][1] == '-' && !cmd[1][2]))
	{
		path = get_value_of_var("HOME", env, exit_status);
		if (!path)
			return (print_error(*cmd, "HOME not set (＠´ー`)ﾉﾞ", 1));
	}
	else if (cmd[2])
		return (print_error(*cmd, "too many arguments ┬┴┬┴┤(･_├┬┴┬┴", 1));
	else
		path = get_path(cmd[1], env);
	redir.fd_output = 0;
	if (path && *path && chdir(path))
	{
		print_file_error(path, check_file_path_access(path, X_OK));
		redir.fd_output = 1;
	}
	if (path != cmd[1])
		free(path);
	if (redir.fd_output == 0)
		return (update_pwds(env));
	return (redir.fd_output);
}
