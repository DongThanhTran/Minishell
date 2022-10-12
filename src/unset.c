/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 22:56:12 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/12 20:55:10 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_env(char *key, t_env *env)
{
	(void)key;
	(void)env;
	// t_env			*tmp;
	// char			*str;
	// int				len;
	// int				i;

	// len = ft_strlen(key);
	// tmp = env;
	// while (tmp && ft_strncmp(tmp->key, key, len) != 0)
	// 	tmp = tmp->next;
	// if (!tmp)
	// 	return ;
	// while (env->next != tmp)
	// 	env = env->next;
	// env->next = tmp ->next;
	// free(tmp->key);
	// free(tmp->value);
	// free(tmp);
}

/*
    Note: program data array update function
*/