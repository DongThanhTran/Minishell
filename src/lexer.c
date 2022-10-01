/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:54:51 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/01 20:01:55 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollar_len(char *str)
{
	if (*str == '?')
		return (1);
	return (ft_name_len(str));
}

// moet \n er wel in?
// miss moeten we isspace aanpassen
static int	get_type(char type)
{
	if (type == '|')
		return (pipe_char);
	else if (type == '<')
		return (infile);
	else if (type == '>')
		return (outfile);
	else if (type == '$')
		return (dollar);
	else if (type == '\"')
		return (dquote);
	else if (type == '\'')
		return (quote);
	else if (type == '\n')
		return (newline);
	return (1);
}

static t_token	*ft_symbol_token(char *prompt)
{
	t_token			*token;
	t_token_type	type;
	unsigned int	length;

	length = 1;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	type = get_type(*prompt);
	if (type == dollar)
		length += dollar_len(&prompt[1]);
	if ((type == infile && prompt[1] == '<') || \
		(type == outfile && prompt[1] == '>'))
	{
		length++;
		if (type == infile)
			type = here_doc;
		else
			type = append_outfile;
	}
	token->token_type = type;
	token->value = ft_substr(prompt, 0, length);
	token->len = length;
	return (token);
}

static t_token	*ft_word_token(char *prompt)
{
	t_token			*new;
	unsigned int	idx;

	idx = 0;
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token_type = word;
	while (!ft_strchr(SYMBOLS, prompt[idx]))
		idx++;
	new->value = ft_substr(prompt, 0, idx);
	new->len = idx;
	return (new);
}

t_token	*ft_lexer(char *prompt)
{
	t_token	*tokens;
	t_token	*token;

	tokens = malloc(sizeof(t_token));
	if (!tokens)
		return (NULL);
	while (*prompt)
	{
		while (*prompt && ft_isspace(*prompt))
			prompt++;
		if (ft_strchr(SYMBOLS, *prompt))
			token = ft_symbol_token(prompt);
		else
			token = ft_word_token(prompt);
		ft_token_add_back(tokens, token);
		prompt += token->len;
	}
	return (tokens);
}
