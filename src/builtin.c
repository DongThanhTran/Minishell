/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 19:29:27 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/27 20:02:39 by dtran         ########   odam.nl         */
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

int	builtin_unchange(char **command)
{
	size_t	len;

	if (!command)
		return (0);
	len = ft_strlen(*command) + 1;
	// if (!ft_strncmp(*command, "echo", len))
	// 	echo(command);
	// else if (!ft_strncmp(*command, "env", len))
	// 	env();
	else if (!ft_strncmp(*command, "pwd", len))
		pwd();
	// else
	// 	return (0);
	return (1);
}
