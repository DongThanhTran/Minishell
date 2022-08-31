/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 15:12:18 by dtran         #+#    #+#                 */
/*   Updated: 2022/05/30 15:17:20 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error_exit(char *str, int exit_code)
{
	ft_putendl_fd(str, 2);
	exit(exit_code);
}
