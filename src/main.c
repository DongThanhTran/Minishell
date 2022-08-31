/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:32:02 by dtran         #+#    #+#                 */
/*   Updated: 2022/08/31 17:58:20 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	char	*cmd_line;

	cmd_line = readline("prompt>");
	// lexer();
	free(cmd_line);
	return (0);
}
