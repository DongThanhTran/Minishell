/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:32:02 by dtran         #+#    #+#                 */
/*   Updated: 2022/09/06 20:28:29 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// init functie voor argc argv + de fd's

t_env	*clear_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = temp;
	}
	return (NULL);
}

static bool	set_env_key_var(t_env *env, char *env_str)
{
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	while (env_str[len1] != '=')
		len1++;
	while (env_str[len1 + len2 + 1])
		len2++;
	env->key = ft_calloc(sizeof(char), len1 + 1);
	env->value = ft_calloc(sizeof(char), len2 + 1);
	if (!env->key || !env->value)
	{
		free(env->key);
		free(env->value);
		free(env);
		return (false);
	}
	ft_memcpy(env->key, env_str, len1);
	ft_memcpy(env->value, (env_str + len1 + 1), len2);
	return (true);
}

bool	add_var(t_env **head, char *env_str)
{
	t_env	*tmp;
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (false);
	if (!set_env_key_var(new, env_str))
		return (false);
	if (*head == NULL)
	{
		*head = new;
		return (true);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (true);
}

t_env	*get_env(char **envp)
{
	t_env	*env;

	env = NULL;
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (!add_var(&env, *envp))
			return (clear_env(env));
		envp++;
	}
	return (env);
}

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	t_token	*tokens;

	signal(SIGINT, sighandler);

	(void)argc;
	(void)argv;
	g_shelly.env = get_env(envp);

	while (1)
	{
		cmd_line = readline("prompt>");
		if (!cmd_line)
			break ;
		if (cmd_line && *cmd_line)
			add_history(cmd_line);
		// tokens = lexer(cmd_line);
		//parsen???
		free(cmd_line);
		// close fd's?
		cmd_line = NULL;
	}

	// g_shelly = get_env(envp);
	// cmd_line = readline("prompt>");
	// g_shelly.token = lexer();
	return (0);
}

// int	main(int argc, char *argv[], char **envp)
// {
// 	char	*cmd_line;
// 	t_token	*tokens;

// 	g_shelly = get_env(envp);
// 	// fd init????
// 	while (1)
// 	{
// 		cmd_line = readline("prompt>");
// 		if (!cmd_line)
// 			break ;
// 		if (cmd_line && *cmd_line)
// 			add_history(cmd_line);
// 		tokens = lexer(cmd_line);
// 		//parsen???
// 		free(cmd_line);
// 		// close fd's?
// 		cmd_line = NULL;
// 	}
// 	return (0);
// }
