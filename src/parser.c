/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/02 11:51:17 by mlammert      #+#    #+#                 */
/*   Updated: 2022/11/30 11:31:43 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**ft_parse_tokens(t_token *token)
{
	char	**res;
	int		len;

	len = ft_len_process(&token);
	if (len == 1)
	{
		res = ft_split(token->value, ' ');
		if (res != NULL && *res != NULL)
		{
			token = token->prev;
			ft_token_del(token->next);
			return (res);
		}
		free(res);
	}
	res = malloc(sizeof(*res) * (len + 1));
	ft_checkmalloc(res);
	res[len] = NULL;
	while (len--)
	{
		res[len] = ft_strdup(token->value);
		token = token->prev;
		ft_token_del(token->next);
	}
	return (res);
}

static int	ft_get_pipe(int *fd, t_env *env)
{
	int				pipefds[2];
	t_shell_data	*sd;

	sd = obtain_sd(env);
	ft_pipe(pipefds);
	if (*fd == STDOUT_FILENO)
		*fd = pipefds[1];
	else
		ft_close(pipefds[1]);
	sd->pipe_set = 1;
	return (pipefds[0]);
}

static int	ft_redirect(t_env *env, t_token *token, int *fd, int flags)
{
	t_shell_data	*sd;

	sd = obtain_sd(env);
	token = token->prev;
	ft_token_del(token->next);
	token = token->next;
	if (*fd > STDERR_FILENO)
		ft_close(*fd);
	*fd = open(token->value, flags, 0644);
	if (*fd < 0)
	{
		sd->exit_code = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(token->value);
		return (-1);
	}
	ft_token_del(token);
	return (0);
}

static int	ft_set_fds(t_env *env, t_token *token, int fd[2])
{
	t_token			*temp;
	t_token_type	type;
	int				err;

	err = 0;
	while (token->next)
	{
		temp = token->next;
		type = temp->token_type;
		if (type == pipe_char)
			return (ft_get_pipe(&fd[1], env));
		else if (type == here_doc)
			err = (ft_ex_heredoc(env, temp, &fd[0]));
		else if (type == inf)
			err = (ft_redirect(env, temp, &fd[0], O_RDONLY));
		else if (type == outf)
			err = ft_redirect(env, temp, &fd[1], O_WRONLY | O_CREAT | O_TRUNC);
		else if (type == append_outfile)
			err = ft_redirect(env, temp, &fd[1], O_WRONLY | O_CREAT | O_APPEND);
		else
			token = token->next;
		if (err)
			return (err);
	}
	return (0);
}

void	ft_parser(t_token *tokens, t_env *env, int pipefd)
{
	int				fd[3];
	pid_t			pid;
	char			**command;
	t_shell_data	*sd;

	sd = obtain_sd(env);
	fd[0] = pipefd;
	fd[1] = STDOUT_FILENO;
	pipefd = ft_set_fds(env, tokens, fd);
	if (pipefd < 0)
		return ;
	fd[2] = pipefd;
	command = ft_parse_tokens(tokens);
	pid = ft_execute(command, fd, env);
	ft_free_all(command);
	if (pipefd)
	{
		ft_token_del(tokens->next);
		ft_parser(tokens, env, pipefd);
	}
	else
		wait(&pid);
	sd->pipe_set = 0;
}
