/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 23:38:06 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/16 16:55:57 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_loop_input(t_shell_data *sd, char *delim)
{
	char	*prompt;
	int		fds[2];
	int		length;

	ft_pipe(fds);
	length = ft_strlen(delim);
	while (1)
	{
		prompt = ft_prompt_check("> ");
		if (sd->sigint_heredoc == 2)
		{
			free(prompt);
			ft_close(fds[0]);
			ft_close(fds[1]);
			return (-1);
		}
		if (!prompt || !ft_strncmp(prompt, delim, length + 1))
			break ;
		write(fds[1], prompt, ft_strlen(prompt));
		write(fds[1], "\n", 1);
		free(prompt);
	}
	ft_close(fds[1]);
	return (fds[0]);
}

int	ft_ex_heredoc(t_env *env, t_token *token, int *fd)
{
	t_shell_data	*sd;

	sd = obtain_sd(env);
	token = token->prev;
	ft_token_del(token->next);
	token = token->next;
	if (*fd > STDERR_FILENO)
		ft_close(*fd);
	sd->sigint_heredoc = 1;
	*fd = ft_loop_input(sd, token->value);
	sd->sigint_heredoc = 0;
	if (*fd < 0)
		return (-1);
	ft_token_del(token);
	return (0);
}
