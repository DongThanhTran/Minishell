/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:42:11 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/12 11:26:02 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_syntax_error(char *str, t_env *env)
{
	t_shell_data	*sd;

	sd = obtain_sd(env);
	sd->exit_code = 2;
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putendl_fd(str, 2);
	return (-1);
}

int	ft_len_process(t_token **token)
{
	int	len;

	len = 0;
	while ((*token)->next && (*token)->next->token_type != pipe_char)
	{
		len++;
		(*token) = (*token)->next;
	}
	return (len);
}

void	ft_free_all(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
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
