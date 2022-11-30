/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 22:56:12 by mlammert      #+#    #+#                 */
/*   Updated: 2022/11/30 19:42:51 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//to do:
// moeten na het unsetten van env, ook weer de char ** updaten.

// static void	free_exp_var(char *key, t_local *exp)
// {
// 	t_local	*tmp;

// 	while (exp)
// 	{
// 		if (ft_strncmp(exp->key, key, ft_strlen(key)) == 0)
// 		{
// 			tmp = exp;
// 			exp = tmp->next;
// 			free(tmp->key);
// 			free(tmp);
// 		}
// 		exp = exp->next;
// 	}
// }

// void	unset_export_var(char *key, t_env *env)
// {
// 	t_shell_data	*sd;
// 	t_local			*exp;
// 	t_local			*tmp;

// 	sd = obtain_sd(env);
// 	exp = sd->export;
// 	if (exp->key == NULL)
// 		return ;
// 	if (ft_strncmp(exp->key, key, ft_strlen(key)) == 0)
// 	{
// 		tmp = exp;
// 		if (exp->next == NULL)
// 		{
// 			free(exp->key);
// 			exp->key = NULL;
// 			return ;
// 		}
// 		exp = exp->next;
// 		free(tmp->key);
// 		free(tmp);
// 		// printf("hello: %s\n", exp->key);
// 		// printf("hello: %p\n", exp);
// 		return ;
// 	}
// 	free_exp_var(key, exp);
// }

void	unset_env(char *key, t_env *env)
{
	t_env			*tmp;
	t_env			*hold;
	int				len;
	t_shell_data	*sd;

	tmp = env;
	sd = obtain_sd(env);
	if (!ft_strchr(key, '='))
		return (delete_local_export(key, sd));
	len = ft_strlen(key);
	while (tmp && (ft_strncmp(tmp->key, key, len - 1) != 0))
		tmp = tmp->next;
	if (!tmp)
		return ;
	if (env == tmp)
	{
		env = env->next;
		// free(tmp->key);
		// free(tmp->value);
		// free(tmp);
		return ;
	}
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
