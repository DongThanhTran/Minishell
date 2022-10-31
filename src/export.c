/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 20:12:08 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/31 18:54:14 by dtran         ########   odam.nl         */
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
		ft_putstr_fd(command, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (0);
	}
	return (length);
}

static void	ft_print_env(t_shell_data *sd)
{
	int	i;

	i = 0;
	sort_env(sd->env);
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
		length = validate_export(commands[i]);
		if (length)
		{
			sub = ft_substr(commands[i], 0, length);
			unset_env(commands, env);
			free(sub);
			add_var(&env, commands[i]);
		}
		else
			sd->exit_code = 1;
		i++;
	}
}

// remninder:
// export a b c moet ik export wel opgeslagen worden en niet in env
// export i=blabla moet het wel in env worden opgeslagen en ook in export