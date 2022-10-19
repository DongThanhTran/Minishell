/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   systemcalls.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 21:35:23 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/19 21:35:23 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_dup2(int fd_one, int fd_two)
{
    int res;

    res = dup2(fd_one, fd_two);
    if (res < 0)
        ft_error_exit("Dup2 failed", EXIT_FAILURE);
    return (res);
}