/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/02 13:02:59 by mlammert      #+#    #+#                 */
/*   Updated: 2022/11/26 14:05:25 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/stat.h>

static int	ft_close_fds(int fds[2])
{
	if (fds[0] > STDERR_FILENO)
		ft_close(fds[0]);
	if (fds[1] > STDERR_FILENO)
		ft_close(fds[1]);
	return (0);
}

static char	*find_path_local(char *str)
{
	struct stat	finfo;

	if (!ft_strncmp(str, ".", 2))
	{
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_error_exit(".: usage: . filename [arguments]", 2);
	}
	stat(str, &finfo);
	if (S_ISDIR(finfo.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_error_exit(": is a directory", 128);
	}
	if (access(str, F_OK) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(str);
		if (access(str, F_OK))
			exit(128);
		exit(126);
	}
	return (str);
}

static char	*ft_find_paths(char *command, char **paths)
{
	char	*tmp;
	int		idx;

	idx = 0;
	if (ft_strncmp(command, "", 2) != 0)
	{
		while (paths[idx])
		{
			tmp = ft_strjoin(paths[idx], "/");
			free(paths[idx]);
			paths[idx] = ft_strjoin(tmp, command);
			free(tmp);
			if (!access(paths[idx], F_OK))
				return (ft_strdup(paths[idx]));
			idx++;
		}
	}
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

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
			return (find_path_local(command));
		paths = ft_split(path_from_env, ':');
		if (!paths)
			ft_error_exit("split failed", EXIT_FAILURE);
		path = ft_find_paths(command, paths);
		ft_free_all(paths);
	}
	else
		path = find_path_local(command);
	return (path);
}

pid_t	ft_execute(char **commands, int fds[2], t_env *env)
{
	t_shell_data	*sd;
	pid_t			pid;
	char			*path;

	if (!*commands || builtin_change(commands, env))
		return (ft_close_fds(fds));
	sd = obtain_sd(env);
	pid = ft_fork(env);
	if (!pid)
	{
		ft_dup2(fds[0], STDIN_FILENO);
		ft_dup2(fds[1], STDOUT_FILENO);
		if (builtin_unchange(commands, env))
			exit(EXIT_SUCCESS);
		path = ft_getpath(*commands, env);
		execve(path, commands, sd->env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	ft_close_fds(fds);
	return (pid);
}
