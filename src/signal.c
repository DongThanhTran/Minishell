/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 17:26:19 by dtran         #+#    #+#                 */
/*   Updated: 2022/11/19 19:43:53 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sighandler(int signum)
{
	extern int		rl_done;
	t_shell_data	*sd;
	int				out;

	sd = obtain_sd(g_env);
	if (signum == SIGINT)
	{
		if (sd->sigint_heredoc == 1)
			sd->sigint_heredoc = 2;
		if (sd->active_processes)
			ft_putchar('\n');
		rl_replace_line("", 0);
		rl_done = 1;
	}
	if (signum == SIGCHLD)
	{
		wait(&out);
		sd->exit_code = WEXITSTATUS(out);
		sd->active_processes--;
	}
	if (signum == SIGQUIT && sd->active_processes)
	{
		ft_putendl_fd("Quit: 3", 2);
		sd->exit_code = 131;
	}
}

static int	sig_no_response(void)
{
	return (0);
}

void	init_signals(void)
{
	extern int	rl_catch_signals;
	extern int	(*rl_event_hook)(void);

	rl_event_hook = sig_no_response;
	rl_catch_signals = 0;
	signal(SIGINT, sighandler);
	signal(SIGCHLD, sighandler);
	signal(SIGQUIT, sighandler);
}
