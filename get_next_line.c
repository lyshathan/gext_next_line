/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ly-sha <ly-sha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:44:56 by ly-sha            #+#    #+#             */
/*   Updated: 2024/11/28 18:20:18 by ly-sha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_until(char *line, char *memory, char c)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen_c(line, 0) + ft_strlen_c(memory, c);
	if (ft_strchr(memory, '\n'))
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
	while (memory[j] && memory[j] != c)
		res[i++] = memory[j++];
	if (ft_strchr(memory, '\n'))
		res[i] = '\n';
	safe_free(line);
	return (res);
}

char	*read_file(int fd, char *memory, char *line)
{
	int	bytes_read;

	bytes_read = BUFFER_SIZE;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, memory, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			ft_bzero(memory, BUFFER_SIZE + 1);
			return (safe_free(line));
		}
		memory[bytes_read] = 0;
		line = join_until(line, memory, '\n');
		if (ft_strchr(line, '\n'))
			break ;
	}
	return (line);
}

void	reset_memory(char *memory)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (memory[i] && memory[i] != '\n')
		i++;
	if (memory[i] == '\n')
		i++;
	j = 0;
	while (memory[i])
	{
		memory[j] = memory[i];
		i++;
		j++;
	}
	memory[j] = 0;
}

char	*get_next_line(int fd)
{
	static char	memory[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (*memory)
		line = join_until(line, memory, '\n');
	if (ft_strchr(line, '\n'))
	{
		reset_memory(memory);
		return (line);
	}
	line = read_file(fd, memory, line);
	if (!line || !*line)
		return (safe_free(line));
	if (!ft_strchr(line, '\n'))
	{
		ft_bzero(memory, BUFFER_SIZE + 1);
		return (line);
	}
	reset_memory(memory);
	return (line);
}
