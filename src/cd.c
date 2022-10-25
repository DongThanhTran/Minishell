/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 23:25:13 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/25 23:25:13 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *cd_into_path(char *path, t_shell_data *sd)
{
    if (chdir(path) < 0)
    {
        ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		perror(path);
		path = NULL;
		sd->last_exit_status = 1;
    }
    return (path);
}

void    ft_cd(char *path, t_env *env)
{
    t_shell_data *sd;
    char        *str;

    sd = obtain_sd(env);
    sd->exit_code = 0;
    path = cd_into_path(path, sd);
    if (path == NULL)
        return ;
    free(sd->pwd);
    sd->pwd = NULL;
    sd->pwd = getcwd(sd->pwd, 0);
    unset_env("PWD");
    str = ft_strjoin("PWD=", sd->pwd);
    add_var(env, str);
    // Still thinking about an different approach to this. When changing directory, 
    //we also need to change the PWD env and OLDPWD env variable. But these are the same oeprations
    // thinking about an easy approach to this via one function, but me tired.
}