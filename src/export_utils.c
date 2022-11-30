/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 14:27:17 by mlammert      #+#    #+#                 */
/*   Updated: 2022/11/30 14:47:12 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_error(char *command, t_shell_data *sd)
{
	ft_putstr_fd("Minishell: export: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	sd->exit_code = 1;
	return (0);
}

int	length_export_line(char *str)
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
