/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:54:51 by dtran         #+#    #+#                 */
/*   Updated: 2022/09/08 18:48:47 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// functies voor word, option, command, infile, outfile
t_token_type	token_specifier(char *cmd_line, unsigned int idx)
{
	if (ft_strncmp(&cmd_line[idx], "<<", 2) == 0)
		return (HEREDOC);
	else if (ft_strncmp(&cmd_line[idx], ">>", 2) == 0)
		return (OUTFILE_APPEND);
	else if (cmd_line[idx] == '<')
		return (INFILE);
	else if (cmd_line[idx] == '>')
		return (OUTFILE);
	else if (cmd_line[idx] == '|')
		return (PIPE);
	else
		return (WORD);
}

// STAPPEN LEXER:
// 1. s_token invullen
// 1a. token type
// 1b. char *value
// 1c. idx (positie van de token)
// 2. post processen
// moet we hier iets returnen?
void	lexer(t_token *head, char *cmd_line)
{
	t_token			*new;
	unsigned int	idx;

	idx = 0;
	while (cmd_line[idx])
	{
		if (ft_strchr(SYMBOLS, cmd_line[idx]))
			new = symbol_token(&cmd_line[idx]);
		else
			new = word_token(cmd_line, idx);
		// idx ????
	}
}

t_token	*symbol_token(char *cmd_line)
{
	t_token			*token;
	t_token_type	type;
	unsigned int	length;

	length = 0;
	type = ft_strchr(SYMBOLS, cmd_line[0]) - SYMBOLS;
	if (type == PIPE)
	// als het een pipe is dan i + 1 is geen spatie of command
	if (type == DQUOTE)
	// itereren tot je nog een " tegenkomt
	if (type == QUOTE)
	// itereren tot je nog een ' tegenkomt
	if (type == SPACE || type == TAB)
	//then idx++;
	if (type == NEWLINE)
	// ???
	if (type == INFILE || type == OUTFILE)
	// zoeken voor de naam van de infile?
	token->token = type;
	token->value = ft_substr(cmd_line, 0, length);
	return (token);
}

unsigned int	word_token(char *cmd_line, int start)
{
	t_token			*new;
	unsigned int	idx;

	idx = 0;
	while (ft_strchr(SYMBOLS, cmd_line[start + idx]) == 0)
		idx++;
	new->token = WORD;
	//ft_substr(cmd_line, start, idx + 1)???
	new->value = ft_substr(cmd_line, start, idx);
	ft_lstadd_back(g_shelly.token, new);
	new->prev = ft_lstlast(g_shelly.token);
	return (idx);
}

// functie om node aan te maken add_token vars te zetten en toevoegen aan linkedl
// post processen moet wel (OPTION pas tokenizen in de postprocessor)
// alles dat tussen quotes dat moet 1 token zijn ofwel 1 arg
