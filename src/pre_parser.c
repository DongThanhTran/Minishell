/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pre_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 15:14:19 by dtran         #+#    #+#                 */
/*   Updated: 2022/10/12 11:36:34 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pre_parser(t_token *token, t_env *env)
{
	int	type;

	while (token)
	{
		type = token->token_type;
		if (type == pipe_char)
		{
			if (token->prev->token_type == begin)
				return (ft_syntax_error("expected command before pipeline", \
					env));
			if (!token->next || token->next == pipe_char)
				return (ft_syntax_error("expected command after pipeline", \
				env));
		}
		if (type == inf || type == outf || type == here_doc || \
			type == append_outfile)
		{	
			if (!token->next || token->next->token_type != word)
				return (ft_syntax_error("expected argument", env));
		}
		token = token->next;
	}
	return (1);
}
