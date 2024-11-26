/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:40:58 by lthan             #+#    #+#             */
/*   Updated: 2024/11/26 08:47:29 by lthan            ###   ########.fr       */
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
		return (NULL);
	res = ft_calloc((ft_strlen(memory) + ft_strlen(buffer) + 1), sizeof(char));
	if (!res)
		return (free(memory), memory = NULL, NULL);
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
	int		red;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	red = BUFFER_SIZE;
	while (red > 0)
	{
		red = read(fd, buffer, BUFFER_SIZE);
		if (red <= 0)
		{
			free(buffer);
			buffer = NULL;
			return (memory);
		}
		memory = join_and_free(memory, buffer);
		ft_bzero(buffer, BUFFER_SIZE);
		if (ft_strchr(memory, '\n'))
			break ;
	}
	free(buffer);
	buffer = NULL;
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
	line = ft_calloc((i + 1), sizeof(char));
	if (!line)
	{
		free(memory);
		memory = NULL;
		return (NULL);
	}
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
		return (free(memory), memory = NULL, memory);
	res = ft_calloc((ft_strlen(temp) + 1), sizeof(char));
	if (!res)
		return (free(memory), memory = NULL, NULL);
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
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(memory);
		memory = NULL;
		return (memory);
	}
	memory = read_until_nl(fd, memory);
	if (!memory)
		return (memory);
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
