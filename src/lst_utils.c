/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 19:23:28 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/22 19:06:04 by dtran         ########   odam.nl         */
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

t_token	*ft_init_token(void)
{
	t_token	*head;

	head = malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	head->next = NULL;
	head->prev = NULL;
	head->value = NULL;
	head->len = 0;
	head->token_type = begin;
	return (head);
}
