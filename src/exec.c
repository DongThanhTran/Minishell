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

// 1. Is opzoek naar het pad van de command
// - Als path niet gevonden is in env (kan na unset(PATH) gebeuren, dan zoeken we naar de lokale versie in bin)
// - via de functie find_bin_path()
 
char	*ft_getpath(char *str, t_env *env)
{
	char	**paths;
	char	*path_from_env;
	char	*path;

	path = NULL;
	if (*str != '.' && !ft_strchr(str, '/'))
	{
		path_from_env = ft_retrieve_env("PATH=", env);
		if (!env_path)
			return (find_bin_path(str));
		paths = ft_split(path_from_env, ":");
		if (!paths)
			ft_error_exit("", EXIT_FAILURE);
		path = ft_find_paths(str, paths);
		ft_free_all(paths);
	}
	else
		path = find_bin_path(str);
	return (path);
}

// HIER ZIJN WIJ
// Made get_path and 
pid_t	ft_execute(char **commands, int fds[2], t_env *env)
{
	t_shell_data	*sd;
	pid_t			pid;
	char			*path;

	if (!*commands || builtin_change(commands))
		return (ft_close_fds(fds));
	sd = obtain_sd(env);
	pid = ft_fork(env);
	if (!pid)
	{
		ft_dup2(fds[0], STDIN_FILENO);
		ft_dup2(fds[1], STDOUT_FILENO);
		if (builtin_unchange(*commands))
			exit(EXIT_SUCCESS);
		path = ft_getpath(*commands);
		execve(path, commands, sd->env);
		ft_error_exit("Minishell: Execve failed", EXIT_FAILURE);
	}
	ft_close_fds(fds);
	return (pid);
}
