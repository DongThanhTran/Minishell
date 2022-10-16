/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/02 13:02:59 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/16 20:05:07 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_close_fds(int fds[2])
{
	if (fds[0] > STDERR_FILENO)
		ft_close(fds[0]);
	if (fds[1] > STDERR_FILENO)
		ft_close(fds[1]);
	return (0);
}

pid_t	ft_fork(t_env *env)
{
	t_shell_data	*sd;
	pid_t			pid;

	sd = obtain_sd(env);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	sd->active_processes++;
	return (pid);
}

// HIER ZIJN WIJ
pid_t	ft_execute(char **args, int fds[2], t_env *env)
{
	t_shell_data	*sd;
	pid_t			pid;
	char			*path;

	if (!*args || builtin_change(args))
		return (ft_close_fds(fds));
	sd = obtain_sd(env);
	pid = ft_fork(env);
	if (!pid)
	{
		ft_dup2
	}
}
