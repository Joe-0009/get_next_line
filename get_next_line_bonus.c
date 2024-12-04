/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:41:25 by yrachidi          #+#    #+#             */
/*   Updated: 2024/12/04 18:30:05 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_free(char *buffer)
{
	if (!buffer)
		return ;
	free(buffer);
}

char	*get_after(char *buffer)
{
	char	*line_location;
	char	*after;
	size_t	len;

	line_location = ft_strchr(buffer, '\n');
	if (!line_location)
		return (NULL);
	line_location++;
	len = ft_strlen(line_location);
	after = ft_calloc(len + 1, 1);
	if (!after)
		return (ft_free(buffer), NULL);
	after = ft_memcpy(after, line_location, len + 1);
	ft_free(buffer);
	return (after);
}

char	*get_before(char *buffer)
{
	char	*before;
	int		i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		before = ft_calloc(i + 1, 1);
		if (!before)
			return (NULL);
		ft_memcpy(before, buffer, i);
		return (before);
	}
	return (buffer);
}

char	*get_line(int fd, char *rbuf)
{
	int		return_bytes;
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (NULL);
	while (1)
	{
		return_bytes = read(fd, buffer, BUFFER_SIZE);
		if (return_bytes < 0)
			return (ft_free(buffer), ft_free(rbuf), NULL);
		if (return_bytes == 0)
			break ;
		buffer[return_bytes] = '\0';
		rbuf = ft_strjoin(rbuf, buffer);
		if (!rbuf)
			return (ft_free(buffer), NULL);
		if (ft_strchr(rbuf, '\n'))
			break ;
	}
	ft_free(buffer);
	return (rbuf);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX || fd > MAX_FD)
		return (NULL);
	buffer[fd] = get_line(fd, buffer[fd]);
	if (!buffer[fd])
	{
		ft_free(buffer[fd]);
		return (NULL);
	}
	if (buffer[fd] && !*buffer[fd])
	{
		ft_free(buffer[fd]);
		return (NULL);
	}
	line = get_before(buffer[fd]);
	buffer[fd] = get_after(buffer[fd]);
	return (line);
}
