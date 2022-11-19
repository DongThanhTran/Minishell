/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:32:02 by dtran         #+#    #+#                 */
/*   Updated: 2022/11/19 14:44:55 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *g_env;

void	print_list(t_token *head)
{
	while (head != NULL)
	{
		printf("length: %d\t type: %d\t value: %s\n", head->len, \
				head->token_type, head->value);
		head = head->next;
	}
}

char	*ft_prompt_check(char *prompt)
{
	char	*str;
	int		len;

	if (isatty(STDIN_FILENO))
	{
		str = readline(prompt);
		if (str && *str)
			add_history(str);
	}
	else
	{
		str = get_next_line(STDIN_FILENO);
		if (!str)
			return (NULL);
		len = ft_strlen(str);
		if (str[len - 1] == '\n')
			str[len - 1] = 0;
	}
	return (str);
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*input;
	t_env		*env;			
	t_token		*head;

	(void)argc;
	(void)argv;
	env = set_env(envp);
	obtain_sd(env);
	init_signals();
	head = ft_init_token();
	ft_checkmalloc(head);
	while (1)
	{
		input = readline("Minishell$ ");
		if (!input)
		{
			ft_putendl_fd("exit", 1);
			rl_clear_history();
			exit(0);
		}
		if (input && *input)
			add_history(input);
		ft_lexer(head, input);
		if (ft_expander(head, env))
			if (ft_pre_parser(head))
				ft_parser(head, env, STDIN_FILENO);
		while (head->next)
			ft_token_del(head->next);
		free(input);
	}
	return (0);
}
