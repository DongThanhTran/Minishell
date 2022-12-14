/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:42:11 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/01 19:15:54 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	add_token(t_token *head, t_token new)
// {

// }

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
