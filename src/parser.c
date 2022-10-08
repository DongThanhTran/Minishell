/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/02 11:51:17 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/08 21:50:51 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_parse_tokens(t_token *token)
{
	char	**res;
	int		len;
	t_token *temp;

	res = NULL;
	temp = token;
	len = ft_len_process(temp);
	printf("CHECK ALUE: %s", temp->value);
	// res = malloc(sizeof(*res) * (len + 1));
	// res[len] = NULL;
	// while (len--)
	// {
	// 	res[len] = ft_strdup(token->value);
	// 	printf("res value: %s\n", res[len]);
	// 	//token = token->prev;
	// 	// ft_token_del(token->next);
	// }
	return (res);
}

void	ft_parser(t_token *tokens)
{
	int		fd[2];
	char	**command;

	fd[0] = STDIN_FILENO;
	command = ft_parse_tokens(tokens);
	// for(int i = 0; i < 3; i++)
	// 	printf("Value: %s\n",command[i]);
	exit(1);
}
