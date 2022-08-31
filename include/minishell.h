/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:57:39 by dtran         #+#    #+#                 */
/*   Updated: 2022/08/31 16:57:39 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>

typedef struct s_command
{
	char	*infile;
	char	*outfile;
	char	**command;
	char	*here_doc;
	int		num;
	char	*line;
}	t_command;

#endif

/*
INPUT -> (LEXER -> PARSER) ->

"infile   cat -a     >>      1"
		  command  heredoc
struct->infile = infile;

*/


/*
commandline input  = "infile cat -c >> output"
char *str = readline --> lees de commandline en returned de commandline zonder \n
str = infile cat -c >> output

str pleuren in een functie die er voor zorgt dat de command wordt verdeelt in de struct.

*/