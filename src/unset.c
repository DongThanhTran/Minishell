/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 22:56:12 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/27 18:37:37 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//to do:
// moeten na het unsetten van env, ook weer de char ** updaten.
void	unset_env(char *key, t_env *env)
{
	t_env	*tmp;
	t_env	*hold;
	int		len;

	tmp = env;
	len = ft_strlen(key);
	while (tmp && (ft_strncmp(tmp->key, key, len - 1) != 0))
		tmp = tmp->next;
	if (!tmp)
		return ;
	while (env->next != tmp)
		env = env->next;
	hold = tmp->next;
	env->next = hold;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	unset(char **strs, t_env *env)
{
	t_shell_data	*sd;
	int				i;

	i = 1;
	sd = obtain_sd(env);
	sd->exit_code = 0;
	while (strs[i])
	{
		unset_env(strs[i], env);
		i++;
	}
	ft_free_all(sd->env);
	set_dpointer_env(env, sd);
}
