/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:28:48 by lthan             #+#    #+#             */
/*   Updated: 2024/11/21 15:48:02 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_and_free(char *memory, char *buffer)
{
	char	*temp;
	size_t	i;
	size_t	j;

	if (!memory)
		return (ft_strdup(buffer));
	temp = ft_strdup(memory);
	if (!temp)
		return (NULL);
	free (memory);
	memory = ft_calloc((ft_strlen(temp) + ft_strlen(buffer) + 1), sizeof(char));
	if (!memory)
	{
		free(temp);
		return (NULL);
	}
	i = -1;
	while (temp[++i])
		memory[i] = temp[i];
	j = 0;
	while (buffer[j])
		memory[i++] = buffer[j++];
	free(temp);
	return (memory);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (str);
}

char	*read_until_nl(char *memory, int fd)
{
	char	*buffer;
	int		red;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	red = BUFFER_SIZE;
	while (red < 0)
	{
		red = read(fd, buffer, BUFFER_SIZE);
		if (red < 0)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
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

char	*set_line(const char *memory)
{
	size_t	i;
	char	*line;

	if (!memory)
		return (NULL);
	i = 0;
	while (memory[i] && memory[i] != '\n')
		i++;
	if (ft_strchr(memory, '\n'))
		i++;
	line = calloc((i + 1), sizeof(char));
	// printf("len line = %zu\n", i);
	if (!line)
		return (NULL);
	i = 0;
	while (memory[i] && memory[i] != '\n')
	{
		line[i] = memory[i];
		i++;
	}
	if (ft_strchr(memory, '\n'))
		line[i] = '\n';
	return (line);
}

char	*reset_memory(char *memory)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	while (memory[i] && memory[i] != '\n')
		i++;
	if (!memory[i])
	{
		free(memory);
		return (NULL);
	}
	temp = ft_calloc((ft_strlen(memory) - i), sizeof(char));
	if (!temp)
	{
		free(memory);
		memory = NULL;
		return (NULL);
	}
	j = 0;
	i++;
	while (memory[i])
	{
		temp[j] = memory[i];
		i++;
		j++;
	}
	free(memory);
	memory = NULL;
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(memory);
		memory = NULL;
		return (NULL);
	}
	// printf("memory 1 = |%s|\n", memory);
	memory = read_until_nl(memory, fd);
	// printf("memory 2 = |%s|\n", memory);

	// if (memory && !*memory)
	// {
	// 	free(memory);
	// 	memory = NULL;
	// 	return (NULL);
	// }
	if (!memory || !*memory)
	{
		if (memory)
			free(memory);
		return (NULL);
	}
	if (!ft_strchr(memory, '\n'))
	{
		line = ft_strdup(memory);
		free(memory);
		memory = NULL;
		return (line);
	}
	line = set_line(memory);
	memory = reset_memory(memory);
	if (!*memory)
	{
		free(memory);
		memory = NULL;
	}
	// printf("memory 3 = |%s|\n", memory);
	return (line);
}
