/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:32:02 by dtran         #+#    #+#                 */
/*   Updated: 2022/11/22 17:59:57 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *g_env;

void	ft_init_pd(t_env *env)
{
	init_signals();
	obtain_sd(env);
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
		if (!str)
		{
			ft_putendl_fd("exit", 1);
			rl_clear_history();
			return (NULL);
		}
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
	ft_init_pd(env);
	head = ft_init_token();
	ft_checkmalloc(head);
	while (1)
	{
		input = ft_prompt_check("Minishell$ ");
		if (!input)
			break ;
		ft_lexer(head, input);
		if (ft_expander(head, env))
			if (ft_pre_parser(head))
				ft_parser(head, env, STDIN_FILENO);
		while (head->next)
			ft_token_del(head->next);
		free(input);
	}
	return (clear_sd(env));
}
