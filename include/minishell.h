/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:57:39 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/11 21:52:54 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SYMBOLS "|<>$\"\' \t\n"

// Includes
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <libft.h>

extern int	g_exitcode;

// Token definitions
typedef enum e_token_type
{
	pipe_char,
	inf,
	outf,
	dollar,
	dquote,
	quote,
	space,
	tab,
	newline,
	here_doc,
	append_outfile,
	word,
	begin
}	t_token_type;

// Token
typedef struct s_token
{
	t_token_type	token_type;
	char			*value;
	int				len;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

// Environment in list
typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// shell data
typedef struct s_shell_data {
	int		exit_code;
	char	**env;
	char	*pwd;
	int		env_lines_number;
	int		active_processes;
}	t_shell_data;

// typedef struct s_program_data
// {
// 	char	**env;
// 	int		last_exit_status;
// 	int		heredoc_sigint;
// }			t_program_data;

// env
t_env	*set_env(char **envp);
t_env	*clear_env(t_env *env);
char	*ft_get_env(t_token *token, t_env *env);

// lexer
void	ft_lexer(t_token *head, char *prompt);

// sigs
void	init_signals(void);

// utils
int		ft_name_len(char *str);
int		ft_syntax_error(char *str);
int		ft_len_process(t_token **token);
void	ft_free_all(char **arr);

// list utils
void	ft_token_add_back(t_token *token, t_token *new);
void	ft_token_del(t_token *token);
t_token	*ft_init_token(void);

// pre-parser
int		ft_pre_parser(t_token *token);

// heredoc
int		ft_ex_heredoc(t_token *token, int fd);

// parser
void	ft_parser(t_token *tokens);

// expander
int		ft_expander(t_token *head, t_env *env);

#endif
