/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:54:01 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/29 15:54:01 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_echo(char **strs)
{
    int     newline;
    int     idx;

    if (!strs[1])
        return (ft_putchar_fd('\n', 1));
    idx = 1;
    newline = ft_strncmp(strs[1], "-n", 3);
    if (!newline)
        idx++;
    while (!ft_strncmp(strs[idx], "-n", 3))
        idx++;
    while (strs[idx])
    {
        ft_putstr(strs[idx]);
        if (strs[idx + 1])
            ft_putchar(' ');
        idx++;
    }
    if (newline)
        ft_putchar('\n');
}