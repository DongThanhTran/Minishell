/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 19:29:27 by dtran         #+#    #+#                 */
/*   Updated: 2022/11/20 13:55:01 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_change(char **commands, t_env *env)
{
	size_t	len;

	if (!commands)
		return (0);
	len = ft_strlen(*commands) + 1;
	if (!ft_strncmp(*commands, "unset", len))
		unset(commands, env);
	else if (!ft_strncmp(*commands, "exit", len))
		ft_exit(commands, env);
	else if (!ft_strncmp(*commands, "export", len))
		ft_export(commands, env);
	else if (!ft_strncmp(*commands, "cd", len))
		ft_cd(commands[1], env);
	else
		return (0);
	return (1);
}

int	builtin_unchange(char **command, t_env *env)
{
	size_t	len;

	if (!command)
		return (0);
	len = ft_strlen(*command) + 1;
	if (!ft_strncmp(*command, "echo", len))
		ft_echo(command, env);
	else if (!ft_strncmp(*command, "env", len) && !*(command + 1))
		ft_env(env);
	else if (!ft_strncmp(*command, "pwd", len))
		ft_pwd(env);
	else
		return (0);
	return (1);
}
