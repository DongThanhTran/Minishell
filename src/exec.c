/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/02 13:02:59 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/21 21:53:35 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_close_fds(int fds[2])
{
	if (fds[0] > STDERR_FILENO)
		ft_close(fds[0]);
	if (fds[1] > STDERR_FILENO)
		ft_close(fds[1]);
	return (0);
}

static char	*find_bin_path(char *str)
{

}

static char	*ft_find_paths(char *command, char **paths)
{
	char	*tmp;
	int		idx;

	idx = 0;
	while (paths[idx])
	{
		tmp = ft_strjoin(paths[idx], "/");
		free(paths[idx]);
		paths[idx] = ft_strjoin(tmp, command);
		free(tmp);
		if (!acces(paths[idx], F_OK))
			return (ft_strdup(paths[idx]));
		idx++;
	}
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

// 1. Is opzoek naar het pad van de command
// - Als path niet gevonden is in env (kan na unset(PATH) gebeuren, dan zoeken we naar de lokale versie in bin)
// - via de functie find_bin_path()
 
static char	*ft_getpath(char *command, t_env *env)
{
	char	**paths;
	char	*path_from_env;
	char	*path;

	path = NULL;
	if (*command != '.' && !ft_strchr(command, '/'))
	{
		path_from_env = ft_retrieve_env("PATH=", env);
		if (!path_from_env)
			return (find_bin_path(command));
		paths = ft_split(path_from_env, ':');
		if (!paths)
			ft_error_exit("split failed", EXIT_FAILURE);
		path = ft_find_paths(command, paths);
		ft_free_all(paths);
	}
	else
		path = find_bin_path(command);
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
		path = ft_getpath(*commands, env);
		execve(path, commands, sd->env);
		ft_error_exit("Minishell: Execve failed", EXIT_FAILURE);
	}
	ft_close_fds(fds);
	return (pid);
}
