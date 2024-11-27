/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:40:58 by lthan             #+#    #+#             */
/*   Updated: 2024/11/27 14:23:06 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_and_free(char *memory, char *buffer)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!memory)
		return (ft_strdup(buffer));
	if (!buffer)
		return (safe_free(memory));
	res = malloc((ft_strlen(memory) + ft_strlen(buffer) + 1) * sizeof(char));
	if (!res)
		return (safe_free(memory));
	res[ft_strlen(memory) + ft_strlen(buffer)] = 0;
	i = -1;
	while (memory[++i])
		res[i] = memory[i];
	j = 0;
	while (buffer && buffer[j])
		res[i++] = buffer[j++];
	free (memory);
	memory = NULL;
	return (res);
}

char	*read_until_nl(int fd, char *memory)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (safe_free(memory));
	bytes_read = BUFFER_SIZE;
	while (bytes_read > 0)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			if (bytes_read < 0)
				return (safe_free(memory));
			else if (bytes_read == 0)
				return (memory);
		}
		memory = join_and_free(memory, buffer);
		if (ft_strchr(memory, '\n'))
			break ;
	}
	free(buffer);
	return (memory);
}

char	*set_line(char *memory)
{
	size_t	i;
	char	*line;

	i = 0;
	while (memory[i] && memory[i] != '\n')
		i++;
	if (memory[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (safe_free(memory));
	line[i] = 0;
	i = 0;
	while (memory[i] && memory[i] != '\n')
	{
		line[i] = memory[i];
		i++;
	}
	if (memory[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*reset_memory(char *memory)
{
	char	*res;
	char	*temp;
	size_t	i;

	temp = ft_strchr(memory, '\n');
	if (!temp)
		return (NULL);
	temp++;
	if (!*temp)
		return (safe_free(memory));
	res = malloc((ft_strlen(temp) + 1) * sizeof(char));
	if (!res)
		return (safe_free(memory));
	res[ft_strlen(temp)] = 0;
	i = 0;
	while (temp[i])
	{
		res[i] = temp[i];
		i++;
	}
	free (memory);
	memory = NULL;
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (memory)
			free(memory);
		memory = NULL;
		return (memory);
	}
	memory = read_until_nl(fd, memory);
	if (!memory)
		return (NULL);
	if (!ft_strchr(memory, '\n'))
	{
		line = ft_strdup(memory);
		free(memory);
		memory = NULL;
		return (line);
	}
	line = set_line(memory);
	memory = reset_memory(memory);
	return (line);
}
