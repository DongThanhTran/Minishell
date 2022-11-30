/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 23:25:13 by mlammert      #+#    #+#                 */
/*   Updated: 2022/11/30 10:39:49 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

static void	cd_error(t_shell_data *sd, char *msg, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putendl_fd(msg, 2);
	sd->exit_code = exit_code;
}

static char	*check_path_to_home(char *path, t_env *env, t_shell_data *sd)
{
	char	*env_path;

	env_path = ft_retrieve_env("HOME=", env);
	if (!path)
	{
		if (!env_path)
		{
			cd_error(sd, "HOME not set", 1);
			return (NULL);
		}
		path = ft_strdup(env_path);
	}
	if (path[0] == '~')
	{
		if (!env_path)
			return (getenv("HOME"));
		path = ft_strjoin(env_path, &path[1]);
	}
	free(env_path);
	return (path);
}

static char	*set_path(char	*path, t_env *env, t_shell_data *sd)
{	
	path = check_path_to_home(path, env, sd);
	if (!path)
		return (path);
	if (path[0] == '-')
	{
		path = ft_retrieve_env("OLDPWD=", env);
		if (!path)
			cd_error(sd, "OLDPWD not set", 1);
		else
			ft_putendl_fd(path, 1);
	}
	return (path);
}

static char	*cd_into_path(char *path, t_shell_data *sd, t_env *env)
{
	char	*tmp_path;

	tmp_path = NULL;
	path = set_path(path, env, sd);
	if (!path)
		return (path);
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		perror(path);
		path = NULL;
		sd->exit_code = 1;
	}
	if (!getcwd(tmp_path, PATH_MAX))
	{
		cd_error(sd, "getcwd: cannot access parent directories:\
 No such file or directory", 0);
		path = NULL;
	}
	free(tmp_path);
	return (path);
}

void	ft_cd(char *path, t_env *env)
{
	t_shell_data	*sd;
	char			*str;

	sd = obtain_sd(env);
	sd->exit_code = 0;
	path = cd_into_path(path, sd, env);
	if (path == NULL)
		return ;
	unset_env("OLDPWD", env);
	str = ft_strjoin("OLDPWD=", sd->pwd);
	add_var(&env, str);
	free(str);
	free(sd->pwd);
	sd->pwd = NULL;
	sd->pwd = getcwd(sd->pwd, 0);
	unset_env("PWD", env);
	str = ft_strjoin("PWD=", sd->pwd);
	add_var(&env, str);
	free(str);
	ft_free_all(sd->env);
	set_dpointer_env(env, sd);
}
