/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/20 16:23:01 by mlammert      #+#    #+#                 */
/*   Updated: 2022/11/20 16:26:15 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	if (!ptr)
		return (malloc(size));
	if (!size)
		return (ptr);
	new = malloc(size);
	if (!new)
		return (NULL);
	ft_memcpy(new, ptr, size);
	return (new);
}
