/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:32:02 by dtran         #+#    #+#                 */
/*   Updated: 2022/09/05 17:16:16 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	char	*cmd_line;
	t_token	*tokens;

	g_shelly = get_env(envp);
	// fd init????
	while (1)
	{
		cmd_line = readline("prompt>");
		if (!cmd_line)
			break ;
		add_history(cmd_line);
		tokens = lexer(cmd_line);
		//parsen???
		free(cmd_line);
		// close fd's?
		cmd_line = NULL;
	}
	return (0);
}
