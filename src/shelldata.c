/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shelldata.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 21:26:00 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/12 12:06:00 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TO_DO
//1. finish shell_lvl (FINISHED)
//2. make obtain_cwd (FINISHED)
//3. unset_env
//4. unset_var
//5. env_add maken in export.
//6. test functies waar *env bij toe is gevoegd
//7. ft_parser afmaken
t_shell_data	*obtain_sd(t_env *env)
{
	static t_shell_data	sd;

	if (sd.env)
		return (&sd);
	env_copy(&sd);
	sd.pwd = getcwd(sd.pwd, 0);
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
	char	*new_lvl;
	int		shlvl;

	shlvl = 0;
	value = ft_retrieve_env("SHLVL", env);
	unset_env("SHLVL", env);
	if (!value)
		shlvl = ft_atoi(value);
	free (value);
	value = ft_itoa(shlvl + 1);
	if (!value)
		exit (EXIT_FAILURE);
	new_lvl = ft_strjoin("SHLVL=", value);
	if (!new_lvl)
		exit(EXIT_FAILURE);
	free (value);
	env_add(new_lvl);
	free (new_lvl);
}
