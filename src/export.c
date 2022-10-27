/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 20:12:08 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/27 22:00:05 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// To do:
// The env should be sorted before printing

// wrm '_'?
static int	length_export_line(char *str)
{
	int	idx;

	idx = 0;
	if (!(str[idx] == '_') || ft_isalpha(str[idx]))
		return (0);
	while (str[idx])
	{
		if (str[idx] == '_' || ft_isalnum(str[idx]))
			idx++;
		else
			break ;
		idx++;
	}
	return (idx);
}

static int	validate_export(char *command)
{
	char	*sub_str;
	int		pos;
	int		length;

	sub_str = ft_strchr(command, '=');
	pos = sub_str - command;
	length = length_export_line(command);
	if (!pos || length != pos)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (0);
	}
	return (length);
}

static void	ft_print_env(t_shell_data *sd)
{
	int	i;

	i = 0;
	while (sd->env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(sd->env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

	// Might need to add some check for the input of export.
	// Examples of export command:
	// - export
	// - export hello=world <- might need to check this if it can fail
void	ft_export(char **commands, t_env *env)
{
	t_shell_data	*sd;
	int				i;
	int				length;
	char			*sub;

	i = 1;
	sd = obtain_sd(env);
	sd->exit_code = 0;
	if (commands[1] == NULL)
		ft_print_env(sd);
	while (commands[i])
	{
		length = validate_export(commands[idx]);
		if (length)
		{
			sub = ft_substr(commands[idx], 0, length);
			unset_env(commands, env);
			free(sub);
			add_var(&env, commands[i]);
		}
		else
			sd->exit_code = 1;
		i++;
	}
}
