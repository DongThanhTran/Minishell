/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:32:02 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/03 19:37:10 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_list(t_token *head)
{
	while (head != NULL)
	{
		printf("length: %d\t type: %d\t value: %s\n", head->len, \
				head->token_type, head->value);
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
	env = set_env(envp);
	head = ft_init_token();
	ft_checkmalloc(head);
	while (1)
	{
		input = readline("Minishell$ ");
		if (!input)
		{
			// When ctrl + D is pushed, this will put out the message that it has stopped.
			ft_putendl_fd("exit", 1);
			rl_clear_history();
			exit(0);
		}
		if (input && *input)
			add_history(input);
		ft_lexer(head, input);
		// ft_expander(head->next, env);
		// command = ft_parser(head, en);
		print_list(head);
		while(head->next)
			ft_token_del(head->next);
		free(input);
	}
	return (0);
}
