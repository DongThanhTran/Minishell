/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 20:12:08 by mlammert      #+#    #+#                 */
/*   Updated: 2022/11/22 22:19:24 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	export_error(char *command)
{
	ft_putstr_fd("Minishell: export: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (0);
}

int	export_exists(char *var, t_shell_data *sd)
{
	t_local	*tmp;

	tmp = sd->export;
	if (!tmp->key)
		return (1);
	while (tmp)
	{
		if (ft_strncmp(var, tmp->key, ft_strlen(var)) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	set_export_vars(char *var, t_shell_data *sd)
{
	t_local	*new;
	t_local	*tmp;

	tmp = sd->export;
	if (length_export_line(var) == 0)
		return (export_error(var));
	if (!export_exists(var, sd))
		return (0);
	if (!sd->export->key)
	{
		sd->export->key = ft_strdup(var);
		return (1);
	}
	new = malloc(sizeof(t_local));
	ft_checkmalloc(new);
	new->key = ft_strdup(var);
	new->next = NULL;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

void	delete_local_export(char *command, t_shell_data *sd)
{
	t_local	*tmp;
	t_local *hold;

	tmp = sd->export;
	if (ft_strncmp(tmp->key, command, ft_strlen(tmp->key)) == 0)
	{
		if (sd->export->next)
		{
			sd->export = sd->export->next;
			free(tmp->key);
			free(tmp);
			return ;
		}
		free(tmp->key);
		tmp->key = NULL;
		return ;
	}
	while (tmp->next)
	{
		if (ft_strncmp(tmp->next->key, command, ft_strlen(tmp->next->key)) == 0)
		{
			hold = tmp->next;
			tmp->next = tmp->next->next;
			free(hold->key);
			free(hold);
		}
		tmp = tmp->next;
	}
}

static int	validate_export(char *command, t_shell_data *sd)
{
	char	*sub_str;
	int		pos;
	int		length;

	sd->export->set = 1;
	length = ft_strlen(command);
	if (length == 0)
		return (export_error(command));
	sub_str = ft_strchr(command, '=');
	if (!sub_str)
		return (set_export_vars(command, sd));
	delete_local_export(command, sd);
	sd->export->set = 0;
	pos = sub_str - command;
	length = length_export_line(command);
	if (!pos || length != pos)
		export_error(command);
	return (length);
}

static void	ft_print_env(t_shell_data *sd)
{
	int			i;
	t_local		*local;

	local = sd->export;
	i = 0;
	sort_env(sd->env);
	while (sd->env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(sd->env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	if (local->key)
	{
		while (local)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(local->key, 1);
			ft_putchar_fd('\n', 1);
			local = local->next;
		}
	}
}

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
		length = validate_export(commands[i], sd);
		if (sd->export->set)
			i++;
		else if (length)
		{
			sub = ft_substr(commands[i], 0, (length + 1));
			unset_env(sub, env);
			free(sub);
			add_var(&env, commands[i]);
			i++;
		}
		else
			sd->exit_code = 1;
	}
	ft_free_all(sd->env);
	set_dpointer_env(env, sd);
}

// remninder:
// export a b c moet ik export wel opgeslagen worden en niet in env
// export i=blabla moet het wel in env worden opgeslagen en ook in export