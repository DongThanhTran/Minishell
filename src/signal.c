/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 17:26:19 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/01 17:27:10 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sighandler(int signum)
{
	extern int	rl_done;
	
	// This signal is triggered by ctrl + backslash
	// The subject says it shouldn't do anything. But there is an edge case i dont know yet..
	// if (signum == SIGQUIT && false)
	// {
	// 	printf("HELLOOO");
	// }

	// This signal is triggered by: ctrl + C
	if (signum == SIGINT)
	{
		// Printing out the newline is for a different case, so when just pushing plain ctrl + c, the newline should be omitted.
		// ft_putchar('\n');
		rl_replace_line("", 0);
		rl_done = 1;
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
