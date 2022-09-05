/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:57:39 by dtran         #+#    #+#                 */
/*   Updated: 2022/09/05 17:59:10 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Includes
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <libft.h>

t_shelly	g_shelly;

typedef struct s_env_var {
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

// Token definitions
typedef enum e_token_type
{
	PIPE = 1,
	READ_IN = 2,
	READ_OUT = 3,
	DOLLAR = 4,
	QUOTE2 = 5,
	QUOTE = 6,
	SPACE = 7,
	TAB = 8,
	NEWLINE = 9,
	HERE_DOC = 10,
	READ_OUT_APP = 11,
	WORD = 12,
	START = 13
}	t_token_type;

typedef struct s_token
{
	t_token_type	token;
	char			*value;
}	t_token;

typedef struct s_command {
	char	*path;
	char	**args;
}	t_command;

typedef struct s_shelly {
	t_env_var		*env;
	int				exit_code;
	int				fd_in;
	int				fd_out;
	int				pipe[2];
	pid_t			pid;
	t_command		*cmds;
	size_t			cmd_n;
}	t_shelly;

#endif

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