/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:40:58 by lthan             #+#    #+#             */
/*   Updated: 2024/11/25 15:57:32 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_and_free(char *memory, char *buffer)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!memory)
	{
		res = ft_strdup(buffer);
		return (res);
	}

	if (!buffer)
		return (NULL);
	size_t len  = ft_strlen(memory) + ft_strlen(buffer);
	res = ft_calloc((len + 1), sizeof(char));
	// printf(RED"Mem alloc at %p		--> res in join_and_free\n"RESET, res);
	if (!res)
	{
		free(memory);
		// printf(GREEN"Free alloc at %p		--> memory in join_and_free\n"RESET, memory);
		memory = NULL;
		return (NULL);
	}

	i = 0;
	while (memory && memory[i])
	{
		res[i] = memory[i];
		i++;
	}

	j = 0;
	while (buffer && buffer[j])
	{
		res[i] = buffer[j];
		i++;
		j++;
	}
	free (memory);
	// printf(GREEN"Free alloc at %p		--> memory in join_and_free\n"RESET, memory);
	memory = NULL;
	return (res);
}

char	*read_until_nl(int fd, char *memory)
{
	char* 	buffer;
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
			return memory;
		}

		// printf("buffer = |%s|\n", buffer)
		memory = join_and_free(memory, buffer);

		ft_bzero(buffer, BUFFER_SIZE);
		// printf("%s\n", memory);
		if (ft_strchr(memory, '\n')) {
			break;
		}
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
	// printf(RED"Mem alloc at %p		--> line in set_line\n"RESET, line);
	if (!line)
	{
		free(memory);
		// printf(GREEN"Free alloc at %p		--> memory in set_line (error)\n"RESET, memory);
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
	if (!temp) {
		return NULL;
	}
	temp++;
	if (!*temp)
	{
		free(memory);
		// printf("Free alloc at %p		--> memory in reset_memory\n", memory);
		memory = NULL;
		return (memory);
	}
	// printf("temp = |%s|	--> len = %zu\n", temp, ft_strlen(temp));
	res = ft_calloc((ft_strlen(temp) + 1), sizeof(char));
	// printf(RED"Mem alloc at %p		--> res in reset_memory\n"RESET, res);
	if (!res)
	{
		free(memory);
		// printf(GREEN"Free alloc at %p\n"RESET, memory);
		memory = NULL;
		return (NULL);
	}
	i = 0;
	while (temp[i])
	{
		res[i] = temp[i];
		i++;
	}
	free (memory);
	// printf(GREEN"Free alloc at %p		--> memory in reset_memory\n"RESET, memory);
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
		return memory;
	}
	memory = read_until_nl(fd, memory);
	// printf("> Memory = |%s|\n", memory);
	if (!memory) {
		return memory;
	}
	if (!ft_strchr(memory, '\n'))
	{
		line = ft_strdup(memory);
		free(memory);
		// printf(GREEN"Free alloc at %p		--> memory in get_next_line(no nl in memory)\n"RESET, memory);
		memory = NULL;
		return (line);
	}
	line = set_line(memory);
	// printf("> Line = |%s|\n", line);
	memory = reset_memory(memory);
	// printf("memory END = |%s|\n", memory);
	return (line);
}