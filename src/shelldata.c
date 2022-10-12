/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shelldata.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 21:26:00 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/12 21:37:31 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell_data	*obtain_sd(t_env *env)
{
	static t_shell_data	sd;

	if (sd.env)
		return (&sd);
	copy_env(&sd, env);
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

void	env_copy(t_shell_data *sd, t_env *env)
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
	t_env	*new;

	shlvl = 0;
	value = ft_retrieve_env("SHLVL", env);
	unset_env("SHLVL", env);
	if (!value)
		shlvl = ft_atoi(value);
	free (value);
	value = ft_itoa(shlvl + 1);
	if (!value)
		exit (EXIT_FAILURE);
	new = malloc(sizeof(t_env));
	new->key = ft_strdup("SHLVL");
	new->value = value;
	new->next = NULL;
	while (env->next)
		env = env->next;
	env->next = new;
	free (value);
}
