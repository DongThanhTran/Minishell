/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:57:39 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/02 10:58:26 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SYMBOLS "\"\' \t\n|<>$"

// Includes
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <libft.h>

extern int exitcode;

// Token definitions
typedef enum e_token_type
{
	pipe_char,
	infile,
	outfile,
	dollar,
	dquote,
	quote,
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

// Environment
typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

// env
t_env	*get_env(char **envp);
t_env	*clear_env(t_env *env);

// lexer
t_token	*ft_lexer(char *prompt);

// sigs
void	init_signals(void);

// utils
int		ft_name_len(char *str);

// list utils
void	ft_token_add_back(t_token *token, t_token *new);

#endif
