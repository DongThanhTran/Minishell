// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   expand.c                                           :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2022/10/02 12:38:49 by mlammert      #+#    #+#                 */
// /*   Updated: 2022/10/02 12:38:49 by mlammert      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "../minishell.h"

static void	ft_expand_dollar(t_token *token)
{
	char	*str;

	token->token_type = word;
	if (token->value[1])
	{
		str = 
	}
	else if (token->value[1] == '?')
	{
		free(token->value);
		token->value = ft_itoa(g_exitcode);
	}
}

static void	ft_join_strs(t_token *token)
{
	char	*tmp;

	while (token)
	{
		if (token->token_type == word && token->next && \
			token->next->token_type == word)
		{
			tmp = token->value;
			token->value = ft_strjoin(token->value, token->next->value);
			free(tmp);
			ft_remove_token(token->next);
			token = token->prev;
		}
		if (token->token_type == newline)
		{
			token = token->prev;
			ft_token_del(token->next);
		}
		token = token->next;
	}
}

static int	ft_quotes_expander(t_token *token, t_token_type type)
{
	char	*tmp;

	token->token_type = word;
	free(token->value);
	token->value = ft_strdup("");
	if (!token->next)
		return (ft_syntax_error("missing closing (d)quote"));
	while (token->next->token_type != type)
	{
		if (type == dquote && token->next->token_type == dollar)
			ft_expand_dollar(token->next);
			tmp = token->value;
			token->value = ft_strjoin(token->value, token->next->value);
			free(tmp);
			ft_token_del(token->next);
			if (!token->next)
				return (ft_syntax_error("missing closing (d)quote"));
	}
	ft_remove_token(token->next);
	return (0);
}

int	ft_expander(t_token *head)
{
	t_token	*token;
	int		error;

	token = head;
	while (token)
	{
		if (token->token_type == quote)
			error = ft_quotes_expander(token, quote);
		if (token->token_type == dquote)
			error = ft_quotes_expander(token, dquote);
		if (token->token_type == dollar)
			ft_dollar_expander(token);
		if (token->token_type == here_doc)
			ft_check(token);
		if (error)
			return (error);
		token = token->next;
	}
	ft_join_strs(head);
	return (0);
}
