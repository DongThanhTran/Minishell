/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/25 15:28:01 by dtran         #+#    #+#                 */
/*   Updated: 2022/07/14 17:09:00 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
char	*ft_strdupgnl(const char *str);
char	*ft_strjoingnl(char *str1, char *str2);
char	*ft_strchrgnl(const char *str, int c);
size_t	ft_strlengnl(const char *str);

#endif
