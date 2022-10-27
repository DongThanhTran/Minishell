/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 19:19:15 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/27 19:21:34 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_env *env)
{
	t_shell_data	*sd;

	sd = obtain_sd(env);
	ft_putendl_fd(sd->pwd, 1);
}
