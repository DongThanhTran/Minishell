/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dtran <dtran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/25 14:54:40 by dtran         #+#    #+#                 */
/*   Updated: 2022/07/14 17:08:42 by dtran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*copy_result(char *strbuff)
{
	char	*result;
	int		length;
	int		idx;

	idx = 0;
	length = ft_strchrgnl(strbuff, '\n') - strbuff;
	result = (char *)malloc(sizeof(char) * (length + 2));
	if (!result)
		return (NULL);
	while (idx < length)
	{
		result[idx] = strbuff[idx];
		idx++;
	}
	result[idx] = '\n';
	result[idx + 1] = '\0';
	return (result);
}

static char	*dup_remainder(char *strbuff)
{
	char	*temp;

	temp = ft_strchrgnl(strbuff, '\n') + 1;
	if (*temp)
	{
		temp = ft_strdupgnl(temp);
		if (!temp)
			return (0);
		free (strbuff);
		return (temp);
	}
	free (strbuff);
	return (0);
}

static char	*find_newline(int fd, char **strbuff, int bread)
{
	char	*endres;

	if (ft_strchrgnl(*strbuff, '\n'))
	{
		endres = copy_result(*strbuff);
		if (!endres)
			return (NULL);
		*strbuff = dup_remainder(*strbuff);
		return (endres);
	}
	else if (bread != 0)
		return (get_next_line(fd));
	endres = *strbuff;
	*strbuff = NULL;
	return (endres);
}

static char	*fill_static(int fd, char **strbuff, char *buff, int bread)
{
	char	*temp;

	if (*strbuff == NULL && bread)
	{
		*strbuff = ft_strdupgnl(buff);
		if (!*strbuff)
			return (NULL);
	}
	else
	{
		temp = ft_strjoingnl(*strbuff, buff);
		if (!temp)
			return (NULL);
		*strbuff = temp;
	}
	return (find_newline(fd, strbuff, bread));
}

char	*get_next_line(int fd)
{
	static char	*strbuff[1024];
	char		buff[BUFFER_SIZE + 1];
	int			bread;

	bread = read(fd, buff, BUFFER_SIZE);
	if (fd < 0 || fd > 1023 || bread < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buff[bread] = '\0';
	return (fill_static(fd, &strbuff[fd], buff, bread));
}
