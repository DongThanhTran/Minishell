/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shelldata.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 21:26:00 by dtran         #+#    #+#                 */
/*   Updated: 2022/11/02 20:01:52 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_dpointer_env(t_env *env, t_shell_data *sd)
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
		exit (EXIT_FAILURE); //niet zeker wat we moeten doen in deze situ
	shlvl = ft_atoi(value);
	free (value);
	while (env && (ft_strncmp(env->key, "SHLVL=", len) != 0))
		env = env->next;
	env->value = ft_itoa(shlvl + 1);
	if (env->value == NULL)
		exit (EXIT_FAILURE);
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
	sd.pwd = getcwd(sd.pwd, 0);
	shell_lvl(env);
	return (NULL);
}
