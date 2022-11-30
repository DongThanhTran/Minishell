/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shelldata.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 21:26:00 by dtran         #+#    #+#                 */
/*   Updated: 2022/11/30 17:49:02 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_dpointer_env(t_env *env, t_shell_data *sd)
{
	t_env			*tmp;
	int				len;
	char			*str;

	len = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	sd->env = malloc(sizeof(char *) * (len + 1));
	ft_checkmalloc(sd->env);
	sd->env[len] = NULL;
	while (len--)
	{
		str = ft_strjoin(env->key, env->value);
		sd->env[len] = str;
		env = env->next;
	}
}

static void	shell_lvl(t_env *env)
{
	char	*value;
	int		shlvl;
	int		len;

	shlvl = 0;
	len = ft_strlen("SHLVL=");
	value = ft_retrieve_env("SHLVL=", env);
	if (!value)
		exit (EXIT_FAILURE);
	shlvl = ft_atoi(value);
	free (value);
	while (env && (ft_strncmp(env->key, "SHLVL=", len) != 0))
		env = env->next;
	env->value = ft_itoa(shlvl + 1);
	if (env->value == NULL)
		exit (EXIT_FAILURE);
}

// Free all
static void	init_export(t_shell_data *sd)
{
	sd->export = malloc(sizeof(t_local));
	ft_checkmalloc(sd->export);
	sd->export->key = NULL;
	sd->export->next = NULL;
	sd->export->set = 0;
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

t_shell_data	*obtain_sd(t_env *env)
{
	static t_shell_data	sd;

	if (sd.env)
		return (&sd);
	set_dpointer_env(env, &sd);
	init_export(&sd);
	sd.pwd = getcwd(sd.pwd, 0);
	sd.exit_code = 0;
	shell_lvl(env);
	return (NULL);
}
