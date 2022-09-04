/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:57:39 by dtran         #+#    #+#                 */
/*   Updated: 2022/09/03 19:56:28 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>

typedef enum e_tokens {
	WORD = 1,
	OPTION = 2,
	LESS = 3,
	GREAT = 4,
	PIPE = 5,
	AMPERSAND = 6,
	NEWLINE = 7,
	HEREDOC = 8,
	GREATAMP = 9,
	COMMAND = 10,
	INFILE = 11,
	OUTFILE = 12,
}	t_tokens;

typedef struct s_command
{
	char	*infile;
	char	*outfile;
	char	**command;
	char	*here_doc;
	int		num;
	char	*line;
}	t_command;

typedef struct s_token {
	t_tokens	token;
}	t_token;

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