/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlammert <mlammert@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 20:12:08 by mlammert      #+#    #+#                 */
/*   Updated: 2022/10/25 20:12:08 by mlammert      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The env should be sorted before printing
void    ft_print_env(t_shell_data *sd)
{
    int     i;

    i = 0;
    while(sd->env[i])
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(sd->env[i], 1);
        ft_putchar_fd('\n', 1);
        i++;
    }
}


void    ft_export(char **inputs, t_env *env)
{
    t_shell_data    *sd;
    int             i;

    i = 1;
    sd = obtain_sd(env);
    if (inputs[i] == NULL)
        ft_print_env(sd);
    // Might need to add some check for the input of export.
    // Examples of export command:
    // - export
    // - export hello=world <- might need to check this if it can fail
    while (inputs[i])
    {
        add_var(&env, inputs[i]);
        i++;
    }
}
