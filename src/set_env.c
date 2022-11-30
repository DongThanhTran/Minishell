/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 17:32:11 by dtran         #+#    #+#                 */
/*   Updated: 2022/11/30 17:47:47 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static int	set_env_key_var(t_env *env, char *env_str)
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
		return (0);
	}
	ft_memcpy(env->key, env_str, (len1 + 1));
	// env->key[len1 + 1] = 0;
	ft_memcpy(env->value, (env_str + len1 + 1), len2);
	return (1);
}

int	add_var(t_env **head, char *env_str)
{
	t_env	*tmp;
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (0);
	if (!set_env_key_var(new, env_str))
		return (0);
	if (*head == NULL)
	{
		*head = new;
		return (1);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

char	*ft_retrieve_env(char *key, t_env *env)
{
	int	len;

	len = ft_strlen(key);
	while (env && (ft_strncmp(env->key, key, len) != 0))
		env = env->next;
	if (!env)
		return (NULL);
	return (ft_strdup(env->value));
}

t_env	*set_env(char **envp)
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
