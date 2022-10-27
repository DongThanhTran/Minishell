/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_exp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 20:00:52 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/27 21:04:00 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	number_of_env_lines(char **env)
{
	int	idx;

	idx = 0;
	while (env[idx])
		idx++;
	return (idx);
}

// to do:
// 1. test of dit werkt
// hier checken we op de eerste letter van een line in de env
static int	check_is_sorted(char **env)
{
	int	idx;

	idx = 0;
	while (env[i])
	{
		if (env[i + 1] != NULL)
			if (ft_strncmp(env[i][0], env[i + 1][0], ft_strlen(env[i])) > 0)
				return (0);
		idx++;
	}
	return (1);
}

void	sort_env(char **env)
{
	int		env_lines;
	int		idx;
	char	*tmp;

	env_lines = number_of_env_lines(env);
	while (check_is_sorted(env) == 0)
	{
		idx = 0;
		while (idx < env_lines - 1)
		{
			if (ft_strncmp(env[idx], env[idx + 1], ft_strlen(env[idx])) > 0)
			{
				tmp = env[idx];
				env[idx] = env[idx + 1];
				env[idx + 1] = tmp;
			}
			idx++;
		}
	}
}
