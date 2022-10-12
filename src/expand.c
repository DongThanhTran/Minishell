/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/02 12:38:49 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/12 11:31:19 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_expand_dollar(t_token *token, t_env *env)
{
	char			*str;
	t_shell_data	*sd;

	sd = obtain_sd(env);
	token->token_type = word;
	if (token->value[1] != '?')
	{
		str = ft_get_env(token, env);
		free(token->value);
		if (!str)
			token->value = ft_strdup("");
		else
			token->value = str;
	}
	else if (token->value[1] == '?')
	{
		free(token->value);
		token->value = ft_itoa(sd->exit_code);
	}
	// if (token->next && token->next->token_type == word)
	// {
	// 	str = token->value;
	// 	token->value = ft_strjoin(str, token->next->value);
	// 	free(str);
	// 	ft_token_del(token->next);
	// 	printf("\nCHECK TOKEN VAL: %s\n", token->value);
	// }
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
			ft_token_del(token->next);
			token = token->prev;
		}
		if (token->token_type == space || token->token_type == tab \
			|| token->token_type == newline)
		{
			token = token->prev;
			ft_token_del(token->next);
		}
		token = token->next;
	}
}

static int	ft_quotes_expander(t_token *token, t_token_type type, t_env *env)
{
	char	*tmp;

	token->token_type = word;
	free(token->value);
	token->value = ft_strdup("");
	if (!token->next)
		return (ft_syntax_error("missing closing (d)quote", env));
	while (token->next->token_type != type)
	{
		if (type == dquote && token->next->token_type == dollar && \
			token->next->value[1] != '\0')
			ft_expand_dollar(token->next, env);
		tmp = token->value;
		token->value = ft_strjoin(token->value, token->next->value);
		free(tmp);
		ft_token_del(token->next);
		if (!token->next)
			return (ft_syntax_error("missing closing (d)quote", env));
	}
	ft_token_del(token->next);
	return (0);
}

/*
	set delimiter veranderd de dollar teken naar een word teken,
	zodat dollar expand het niet aanpast
	Voorbeeld: <<$LANG (MOET $LANG BLIJVEN EN NIET DE ENV WAARDEN PAKKEN)
*/
static void	ft_set_delimiter(t_token *token)
{
	if (token->next && token->next->token_type == dollar)
		token->next->token_type = word;
	if (token->next && token->next->token_type == space
		&& token->next->next && token->next->next->token_type == dollar)
		token->next->next->token_type = word;
}

int	ft_expander(t_token *head, t_env *env)
{
	t_token	*token;
	int		error;

	token = head;
	error = 0;
	while (token)
	{
		if (token->token_type == quote)
			error = ft_quotes_expander(token, quote, env);
		if (token->token_type == dquote)
			error = ft_quotes_expander(token, dquote, env);
		if (token->token_type == dollar && token->value[1] != '\0')
			ft_expand_dollar(token, env);
		if (token->token_type == here_doc)
			ft_set_delimiter(token);
		if (error)
			return (error);
		token = token->next;
	}
	ft_join_strs(head);
	return (1);
}
