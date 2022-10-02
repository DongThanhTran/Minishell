/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/02 12:38:49 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/02 12:38:49 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int ft_handle_quotes(t_token *token, t_type type)
// {
//     char    *tmp;

//     token->token_type = word;
//     free(token->value);
//     if (!token->next)
//         return ()
// }

void    ft_expand_dollar(t_token *token, t_env *env)
{
    char    *str;

    token->token_type = word;
    if (token->value[1] != '?')
    {
        str = ft_get_env(token, env);
        free(token->value);
        if (!str)
            token->value = ft_strdup("");
        else
            token->value = str;
    }
    else if (token->value[1] == '?')
    {
        free(token->value);
        token->value = ft_itoa(g_exitcode);
    }
    // if (token->next && token->next->token_type == word)
	// {
	// 	str = token->value;
	// 	token->value = ft_strjoin(str, token->next->value);
	// 	free(str);
	// 	ft_token_del(token->next);
	// }
}


int ft_expander(t_token *head, t_env *env)
{
    t_token         *temp;

    temp = head;
    while (temp)
    {
        // if (temp->token_type == dquote)
        //     // ft_handle_quotes(temp, dquote);
        // if (temp->token_type == quote)
            
        // if (temp->token_type == here_doc)

        if (temp->token_type == dollar)
            ft_expand_dollar(token, env);
        temp = temp->next;
    }
    return (0);
}

