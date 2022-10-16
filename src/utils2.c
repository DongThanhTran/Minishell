/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 15:03:21 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/16 20:04:35 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_close(int fildes)
{
	int	ret;

	ret = close(fildes);
	if (ret < 0)
		ft_error_exit("close failed", EXIT_FAILURE);
	return (ret);
}

int	ft_pipe(int fildes[2])
{
	int	ret;

	ret = pipe(fildes);
	if (ret < 0)
		ft_error_exit("pipe failed", EXIT_FAILURE);
	return (ret);
}

int	ft_dup2(int fd_one, int fd_two)
{
	int	ret;

	ret = dup2(fd_one, fd_two);
	if (ret < 0)
		ft_error_exit("Dup 2 failed", EXIT_FAILURE);
	return (ret);
}

pid_t	ft_fork(t_env *env)
{
	t_shell_data	*sd;
	pid_t			pid;

	sd = obtain_sd(env);
	pid = fork();
	if (pid < 0)
		ft_error_exit ("fork failed", EXIT_FAILURE);
	sd->active_processes++;
	return (pid);
}
