/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:32:02 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/01 20:03:07 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_list(t_token *head)
{
	while (head != NULL)
	{
		printf("length: %d\t type: %d\t value: %s\n", head->len, head->token_type, head->value);
		head = head->next;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*input;
	// char		**command;
	t_token		*head;
	t_env		*env;

	init_signals();
	(void)argc;
	(void)argv;
	env = get_env(envp);
	while (1)
	{
		input = readline("Dit is echt leuk: ");
		if (!input)
		{
			// When ctrl + D is pushed, this will put out the message that it has stopped.
			ft_putendl_fd("exit", 1);
			exit(0);
		}
		if (input && *input)
			add_history(input);
		head = ft_lexer(input);
		// command = ft_parser(head, en);
		print_list(head);
		free(input);
		input = NULL;
	}
	return (0);
}
