/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 18:56:01 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/31 19:03:33 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env *env)
{
	t_shell_data	*sd;
	int				idx;

	idx = 0;
	sd = obtain_sd(env);
	while (sd->env[idx])
	{
		ft_putendl_fd(sd->env[idx], 1);
		idx++;
	}
}
