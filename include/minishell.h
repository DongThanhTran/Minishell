/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:57:39 by dtran         #+#    #+#                 */
/*   Updated: 2022/11/30 19:19:54 by mlammert      ########   odam.nl         */
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
# include <fcntl.h>
# include <get_next_line.h>
# include <libft.h>

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

typedef struct s_local {
	char			*key;
	struct s_local	*next;
	int				set;
}	t_local;

// shell data
typedef struct s_shell_data {
	int				exit_code;
	char			**env;
	char			*pwd;
	int				env_lines_number;
	int				active_processes;
	int				sigint_heredoc;
	int				pipe_set;
	struct s_local	*export;
}	t_shell_data;

extern t_env	*g_env;

// main
char			*ft_prompt_check(char *prompt);

// env
t_env			*set_env(char **envp);
t_env			*clear_env(t_env *env);
char			*ft_get_env(t_token *token, t_env *env);
char			*ft_retrieve_env(char *key, t_env *env);
int				add_var(t_env **head, char *env_str);

// lexer
void			ft_lexer(t_token *head, char *prompt);

// sigs
void			init_signals(void);

// utils
int				ft_syntax_error(char *str);
int				ft_len_process(t_token **token);
void			ft_free_all(char **arr);
int				ft_name_len(char *str);

// utils2
int				ft_close(int fildes);
int				ft_pipe(int fildes[2]);
int				ft_dup2(int fd_one, int fd_two);
pid_t			ft_fork(t_env *env);

// list utils
void			ft_token_add_back(t_token *token, t_token *new);
void			ft_token_del(t_token *token);
t_token			*ft_init_token(void);

// pre-parser
int				ft_pre_parser(t_token *token);

// heredoc
int				ft_ex_heredoc(t_env *env, t_token *token, int *fd);

// shell data
t_shell_data	*obtain_sd(t_env *env);
int				clear_sd(t_env *env);
void			set_dpointer_env(t_env *env, t_shell_data *sd);

// parser
void			ft_parser(t_token *tokens, t_env *env, int pipefd);

// Executor
pid_t			ft_execute(char **args, int fds[3], t_env *env);

// builtin funcs
int				builtin_change(char **commands, t_env *env);
int				builtin_unchange(char **command, t_env *env);

// Expander
int				ft_expander(t_token *head, t_env *env);

// Export
void			delete_local_export(char *command, t_shell_data *sd);

// Export Utils
int				length_export_line(char *str);
int				export_error(char *command, t_shell_data *sd);
int				validate_export(char *command, t_shell_data *sd);
int				set_export_vars(char *var, t_shell_data *sd);
int				export_exists(char *var, t_shell_data *sd);
void			ft_print_env(t_shell_data *sd);

//Built-ins
void			unset_env(char *key, t_env *env);
void			unset(char **strs, t_env *env);
void			ft_exit(char **strs, t_env *env);
void			ft_export(char **commands, t_env *env);
void			ft_cd(char *path, t_env *env);
void			ft_echo(char **strs, t_env *env);
void			ft_env(t_env *env);
void			sort_env(char **env);
void			ft_pwd(t_env *env);

#endif
