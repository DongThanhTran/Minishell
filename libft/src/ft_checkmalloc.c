/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_checkmalloc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/27 15:23:56 by dtran         #+#    #+#                 */
/*   Updated: 2022/05/27 17:06:34 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_checkmalloc(void *ptr)
{
	if (!ptr)
		exit (1);
}
