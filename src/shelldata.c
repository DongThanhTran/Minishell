/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shelldata.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 21:26:00 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/12 11:48:31 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TO_DO
//1. finish shell_lvl
//2. make obtain_cwd
//3. unset_env
//4. unset_var
//5. test functies waar *env bij toe is gevoegd
//6. ft_parser afmaken
t_shell_data	*obtain_sd(t_env *env)
{
	static t_shell_data	sd;

	if (sd.env)
		return (&sd);
	env_copy(&sd);
	// sd.pwd = obtain_cwd(sd.pwd, 0);
	shell_lvl(env);
	return (NULL);
}

int	clear_sd(t_env *env)
{
	t_shell_data	*sd;
	int				exit;

	sd = obtain_sd(env);
	exit = sd->exit_code;
	ft_free_all(sd->env);
	free(sd->pwd);
	return (exit);
}

void	env_copy(t_shell_data *sd)
{
	extern char	**environ;
	int			idx;

	idx = 0;
	while (environ[idx])
		idx++;
	sd->env_lines_number = idx;
	sd->env = malloc(sizeof(char *) * (idx + 1));
	if (!sd->env)
		return ;
	sd->env[idx] = NULL;
	while (idx--)
		sd->env[idx] = ft_strdup(environ[idx]);
}

void	shell_lvl(t_env *env)
{
	char	*value;
	int		shlvl;

	shlvl = 0;
	value = ft_retrieve_env("SHLVL", env);
	unset_env("SHLVL", env);
	// Finish this part..
}
