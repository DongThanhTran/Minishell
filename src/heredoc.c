/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 23:38:06 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/12 11:24:13 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ex_heredoc(t_token *token, int *fd)
{
	fd = 0;

	token = token->prev;
	ft_token_del(token->next);
	token = token->next;
	return (0);
}
