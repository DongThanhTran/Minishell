/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 19:23:28 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/02 16:50:35 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_token_del(t_token *token)
{
	if (!token)
		return ;
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	free(token->value);
	free(token);
}

void	ft_token_add_back(t_token *token, t_token *new)
{
	t_token	*temp;

	temp = token;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	new->next = NULL;
}
