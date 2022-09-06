/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:57:39 by dtran         #+#    #+#                 */
/*   Updated: 2022/09/06 20:51:35 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Includes
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <libft.h>

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

// Token definitions
typedef enum e_token_type
{
	PIPE = 1,
	INFILE = 2,
	OUTFILE = 3,
	HERE_DOC = 5,
	OUTFILE_APPEND = 6,
	OPTION = 7,
	COMMAND = 8,
	ARG = 9,
}	t_token_type;

typedef struct s_token
{
	t_token_type	token;
	char			*value;
	unsigned int	idx;
	unsigned int	length;
}	t_token;

typedef struct s_command {
	char	*path;
	char	**args;
}	t_command;

typedef struct s_shelly {
	t_env		*env;
	t_token		*token;
	int			exit_code;
	int			fd_in;
	int			fd_out;
	int			pipe[2];
	pid_t		pid;
	t_command	*cmds;
	size_t		cmd_n;
}	t_shelly;


t_shelly	g_shelly;


#endif

// token length bepalen is belangrijk zodat je bijv kunt allocaten


// als je export variable en je geeft het geen waarde
// dan is ie ook niet te zien in je env, maar bestaat wel.

// typedef struct s_app_data
// {
// 	char	*env;
// 	int		env_lines;
// }

// typedef struct s_command
// {
// 	char	*infile;
// 	char	*outfile;
// 	char	**command;
// 	char	*here_doc;
// 	int		num;
// 	char	*line;
// } t_command;

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