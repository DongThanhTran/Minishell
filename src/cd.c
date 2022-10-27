/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 23:25:13 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/27 19:43:06 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*cd_into_path(char *path, t_shell_data *sd)
{
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		perror(path);
		path = NULL;
		sd->exit_code = 1;
	}
	return (path);
}

void	ft_cd(char *path, t_env *env)
{
	t_shell_data	*sd;
	char			*str;

	sd = obtain_sd(env);
	sd->exit_code = 0;
	path = cd_into_path(path, sd);
	if (path == NULL)
		return ;
	unset_env("OLDPWD", env);
	str = ft_strjoin("OLDPWD=", sd->pwd);
	add_var(env, str);
	free(str);
	free(sd->pwd);
	sd->pwd = NULL;
	sd->pwd = getcwd(sd->pwd, 0);
	unset_env("PWD", env);
	str = ft_strjoin("PWD=", sd->pwd);
	add_var(env, str);
	free(str);
}
