/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:54:51 by dtran         #+#    #+#                 */
/*   Updated: 2022/09/02 15:50:22 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// splitten op spatie
// functies voor word, option, command, infile, outfile
static int	token_specifier(char *split)
{
	if (split == '<')
		return (LESS);
}

t_command *lexer(char *str)
{

}

// een array out is een token
