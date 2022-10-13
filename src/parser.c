/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/02 11:51:17 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/13 22:59:22 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_parse_tokens(t_token *token)
{
	char	**res;
	int		len;

	len = ft_len_process(&token);
	res = malloc(sizeof(*res) * (len + 1));
	if (!res)
		exit(EXIT_FAILURE);
	res[len] = NULL;
	while (len--)
	{
		res[len] = ft_strdup(token->value);
		token = token->prev;
		ft_token_del(token->next);
	}
	return (res);
}

int	ft_set_fds(t_token *token, int fds[2])
{
	t_token			*temp;
	t_token_type	type;
	// int				err;

	// err = 0;
	while (token->next)
	{
		temp = token->next;
		type = token->token_type;
		if (type == here_doc)
			return (ft_ex_heredoc(temp, &fds[0]));
		else
			token = token->next;
	}
	return (0);
}

int	ft_get_pipe(int *fd)
{
	int	pipefds[2];
	int	err;

	err = pipe(pipefds);
	if (err < 0)
		ft_error_exit("pipe call failed", EXIT_FAILURE);
	if (*fd == STDOUT_FILENO)
		*fd = pipefds[1];
	else
		err = close(pipefds[1]);
		if (err < 0)
			ft_error_exit("pipe close failed", EXIT_FAILURE);
	return (pipefds[0]);
}

void	ft_parser(t_token *tokens)
{
	int		fd[2];
	char	**command;

	fd[0] = STDIN_FILENO;
	command = ft_parse_tokens(tokens);
	ft_free_all(command);
	exit(1);
}
