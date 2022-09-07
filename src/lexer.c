/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:54:51 by dtran         #+#    #+#                 */
/*   Updated: 2022/09/07 23:45:03 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// functies voor word, option, command, infile, outfile
t_token_type	token_specifier(char *cmd_line, unsigned int idx)
{
	if (ft_strncmp(&cmd_line[idx], "<<", 2) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(&cmd_line[idx], ">>", 2) == 0)
		return (OUTFILE_APPEND);
	else if (cmd_line[idx] == '<')
		return (INFILE);
	else if (cmd_line[idx] == '>')
		return (OUTFILE);
	else if (cmd_line[idx] == '|')
		return (PIPE);
	else
		return (COMMAND);
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
			new = symbol_token(cmd_line[idx]);
		else
			new = word_token(cmd_line[idx]);
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
	if (type == DQUOTE)
	if (type == QUOTE)
	if (type == SPACE || type == TAB)
		
	if (type == NEWLINE)
	if (type == INFILE || type == OUTFILE)
	token->token = type;
	token->value = ft_substr(cmd_line, 0, length);
	return (token);
}

t_token	*word_token(char *cmd_line)
{
	unsigned int	idx;

	idx = 0;
	while ()
}

// functie om node aan te maken add_token vars te zetten en toevoegen aan linkedl
// post processen moet wel (OPTION pas tokenizen in de postprocessor)
// alles dat tussen quotes dat moet 1 token zijn ofwel 1 arg
