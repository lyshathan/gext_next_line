/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:28:48 by lthan             #+#    #+#             */
/*   Updated: 2024/11/19 13:11:53 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_until_nl(char *buffer, char *memory, int fd)
{
	size_t	red;
	char	*temp;

	red = BUFFER_SIZE;
	while (red == BUFFER_SIZE)
	{
		// printf("here\n");
		temp = ft_strdup(memory);
		printf("temp = |%s|\n", temp);
		if (memory)
		{
			free(memory);
			memory = NULL;
		}
		red = read(fd, buffer, BUFFER_SIZE);
		printf("buffer = |%s|\n", buffer);
		buffer[BUFFER_SIZE] = 0;
		memory = ft_strjoin(temp, buffer);
		printf("memory = |%s|\n", memory);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	ft_bzero(buffer, BUFFER_SIZE);
	return (memory);
}

char	*get_next_line(int fd)
{
	static char *memory;
	char		*buffer;
	char		*line;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	memory = read_until_nl(buffer, memory, fd);
	printf("memory = %s\n", memory);
	line = NULL;
	return (line);
}