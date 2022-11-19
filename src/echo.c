/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:54:01 by mlammert      #+#    #+#                 */
/*   Updated: 2022/11/19 19:21:49 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print(char **strs, int pos, t_env *env)
{
	char	*env_var;

	while (strs[pos])
	{
		if (ft_strncmp("~", strs[pos], 2) == 0)
		{
			env_var = ft_retrieve_env("HOME=", env);
			ft_putstr(env_var);
		}
		else
			ft_putstr(strs[pos]);
		if (strs[pos + 1])
			ft_putchar(' ');
		pos++;
	}
}

//TODO: Create function to check n's
// minishell: export: `test1': not a valid identifier <- double check

void	ft_echo(char **strs, t_env *env)
{
	int	newline;
	int	idx;

	if (!strs[1])
		return (ft_putchar_fd('\n', 1));
	idx = 1;
	newline = ft_strncmp(strs[1], "-n", 3);
	if (!newline)
		idx++;
	while (!ft_strncmp(strs[idx], "-n", 3))
		idx++;
	ft_print(strs, idx, env);
	if (newline)
		ft_putchar('\n');
}
