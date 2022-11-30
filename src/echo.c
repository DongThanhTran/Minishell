/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:54:01 by mlammert      #+#    #+#                 */
/*   Updated: 2022/11/30 19:35:27 by mlammert      ########   odam.nl         */
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
			if (!env_var)
				env_var = getenv("HOME");
			ft_putstr(env_var);
		}
		else
			ft_putstr(strs[pos]);
		if (strs[pos + 1])
			ft_putchar(' ');
		pos++;
	}
}

int	only_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (!ft_strncmp(str, "-n", 3))
		return (1);
	if (str[i] == '-' && !str[i + 1])
		return (0);
	while (str[i])
	{
		if (str[i] == '-')
		{
			i++;
			continue ;
		}
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **strs, t_env *env)
{
	int		newline;
	int		idx;

	if (!strs[1])
		return (ft_putchar_fd('\n', 1));
	idx = 1;
	newline = ft_strncmp(strs[1], "-n", 3);
	if (!newline)
		idx++;
	while (only_n(strs[idx]))
	{
		newline = 0;
		idx++;
	}
	ft_print(strs, idx, env);
	if (newline)
		ft_putchar('\n');
}
