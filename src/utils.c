/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:42:11 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/02 18:16:12 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_syntax_error(char *str)
{
	g_exitcode = 2;
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putendl_fd(str, 2);
	return (-1);
}

int	ft_name_len(char *str)
{
	int	strlen;
	int	i;

	i = 0;
	strlen = ft_strlen(str);
	if (!(*str == '_' || ft_isalpha(*str)))
		return (0);
	while (i < strlen)
	{
		if (str[i] == '_' || ft_isalnum(str[i]))
			i++;
		else
			break ;
	}
	return (i);
}
