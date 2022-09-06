/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:54:51 by dtran         #+#    #+#                 */
/*   Updated: 2022/09/06 20:13:26 by dtran         ########   odam.nl         */
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

// t_command *lexer(char *str)
// {

// }

// functie om node aan te maken add_token vars te zetten en toevoegen aan linkedl
// post processen moet wel (OPTION pas tokenizen in de postprocessor)
// alles dat tussen quotes dat moet 1 token zijn ofwel 1 arg
