/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 20:12:08 by mlammert      #+#    #+#                 */
/*   Updated: 2022/11/20 17:47:17 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// To do:
// The env should be sorted before printing

static int	length_export_line(char *str)
{
	int	idx;

	idx = 0;
	if (!(str[idx] == '_' || ft_isalpha(str[idx])))
		return (0);
	while (str[idx])
	{
		if (str[idx] == '_' || ft_isalnum(str[idx]))
			idx++;
		else
			break ;
	}
	return (idx);
}
// Does not work atm
void	set_export_vars(char *var, t_shell_data *sd)
{
	char	**new;
	int		len;
	int		i;

	printf("check: %d\n", !*(sd->export));
	len = 5;
	new = (char **)ft_realloc(sd->export, (len + 1) * sizeof(*sd->export));
	new[len + 1] = NULL;
	if (!new)
		ft_free_all(sd->export);
	if (!*(sd->export))
		new[len] = ft_strdup(var);
	else
	{
		i = 0;
		while (i < len)
		{
			new[i] = ft_strdup(sd->export[i]);
			i++;
		}
	}
	sd->export = new;
	free(new);
}

static int	validate_export(char *command, t_shell_data *sd)
{
	char	*sub_str;
	int		pos;
	int		length;

	sub_str = ft_strchr(command, '=');
	if (!sub_str)
		set_export_vars(command, sd);
	pos = sub_str - command;
	length = length_export_line(command);
	if (!pos || length != pos)
	{
		ft_putstr_fd("Minishell: export: ", 2);
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
	printf("\nhecl sd: %s\n", *(sd->export));
	sd->exit_code = 0;
	if (commands[1] == NULL)
		ft_print_env(sd);
	while (commands[i])
	{
		length = validate_export(commands[i], sd);
		if (length)
		{
			sub = ft_substr(commands[i], 0, (length + 1));
			unset_env(sub, env);
			free(sub);
			add_var(&env, commands[i]);
		}
		else
			sd->exit_code = 1;
		i++;
	}
	ft_free_all(sd->env);
	set_dpointer_env(env, sd);
}

// remninder:
// export a b c moet ik export wel opgeslagen worden en niet in env
// export i=blabla moet het wel in env worden opgeslagen en ook in export