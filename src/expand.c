// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   expand.c                                           :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2022/10/02 12:38:49 by mlammert      #+#    #+#                 */
// /*   Updated: 2022/10/02 12:38:49 by mlammert      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"

// // int ft_handle_quotes(t_token *token, t_type type)
// // {
// //     char    *tmp;

// //     token->token_type = word;
// //     free(token->value);
// //     if (!token->next)
// //         return ()
// // }

// void    ft_expand_dollar(t_token *token)
// {
//     char    *str;

//     token->token_type = word;
//     if (token->value[1])
//     {
//         str = 
//     }
//     else if (token->value[1] == '?')
//     {
//         free(token->value);
//         token->value = ft_itoa(exitcode);
//     }
// }


// int ft_expander(t_token *head)
// {
//     t_token         *temp;

//     temp = head;
//     while (temp)
//     {
//         // if (temp->token_type == dquote)
//         //     // ft_handle_quotes(temp, dquote);
//         // if (temp->token_type == quote)
            
//         // if (temp->token_type == here_doc)

//         if (temp->token_type == dollar)
//             ft_expand_dollar(token);
//         temp = temp->next;
//     }
//     return (0);
// }

