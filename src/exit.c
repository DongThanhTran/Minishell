/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 21:02:00 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/22 22:06:20 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned char	ft_exit_atoi(char *str)
{
	unsigned char	num;
	int				min;
	int				idx;

	num = 0;
	min = 0;
	idx = 0;
	if (str[idx] == '-')
	{
		idx++;
		min = 1;
	}
	while (str[idx] == '0' && str[1])
		idx++;
	while (str[idx])
	{
		num = 10 * num + str[idx] - '0';
		idx++;
	}
	if (min)
		num = 256 - num;
	return (num);
}

static int	is_digits(char *str)
{
	int	i;

	if (*str == '-')
		str++;
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **strs, t_env *env)
{
	t_shell_data	*sd;

	sd = obtain_sd(env);
	if (isatty(STDERR_FILENO))
		ft_putstr("exit\n");
	if (!strs[1])
		exit(sd->exit_code);
	if (ft_strlen(strs[1]) > 19 || is_digits(strs[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(strs[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		sd->exit_code = 1;
		exit(255);
	}
	else if (strs[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		sd->exit_code = 2;
	}
	else
		exit(ft_exit_atoi(strs[1]));
}
