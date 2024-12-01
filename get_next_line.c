/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ly-sha <ly-sha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:44:56 by ly-sha            #+#    #+#             */
/*   Updated: 2024/12/01 16:40:05 by ly-sha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_until(char *line, char *buffer, char c)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen_c(line, 0) + ft_strlen_c(buffer, c);
	if (ft_strchr(buffer, '\n'))
		len++;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (safe_free(line));
	res[len] = 0;
	i = 0;
	while (line && line[i])
	{
		res[i] = line[i];
		i++;
	}
	j = 0;
	while (buffer[j] && buffer[j] != c)
		res[i++] = buffer[j++];
	if (buffer[j] == '\n')
		res[i] = '\n';
	safe_free(line);
	return (res);
}

char	*read_file(int fd, char *buffer, char *line)
{
	int	bytes_read;

	bytes_read = BUFFER_SIZE;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			ft_bzero(buffer, BUFFER_SIZE + 1);
			return (safe_free(line));
		}
		buffer[bytes_read] = 0;
		line = join_until(line, buffer, '\n');
		if (!line)
			return (ft_bzero(buffer, BUFFER_SIZE + 1));
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (line);
}

void	reset_buffer(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i])
	{
		buffer[j] = buffer[i];
		i++;
		j++;
	}
	buffer[j] = 0;
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (*buffer)
		line = join_until(line, buffer, '\n');
	if (*buffer && !line)
		return (ft_bzero(buffer, BUFFER_SIZE + 1));
	if (ft_strchr(buffer, '\n'))
	{
		reset_buffer(buffer);
		return (line);
	}
	line = read_file(fd, buffer, line);
	if (!line || !*line)
		return (safe_free(line));
	if (!ft_strchr(buffer, '\n'))
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		return (line);
	}
	reset_buffer(buffer);
	return (line);
}
