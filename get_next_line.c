/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:28:48 by lthan             #+#    #+#             */
/*   Updated: 2024/11/19 15:01:49 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_until_nl(char *buffer, char *memory, int fd, int *red)
{
	char	*temp;

	*red = BUFFER_SIZE;
	while (*red == BUFFER_SIZE)
	{
		// printf("here\n");
		temp = ft_strdup(memory);
		// printf("temp = |%s|\n", temp);
		free(memory);
		memory = NULL;
		*red = read(fd, buffer, BUFFER_SIZE);
		// printf("buffer = |%s|\n", buffer);
		buffer[BUFFER_SIZE] = 0;
		memory = ft_strjoin(temp, buffer);
		free(temp);
		// printf("memory = |%s|\n", memory);
		if (ft_strchr(buffer, '\n'))
		{
			ft_bzero(buffer, BUFFER_SIZE);
			break ;
		}
		ft_bzero(buffer, BUFFER_SIZE);
	}
	return (memory);
}

char	*set_line(const char *memory)
{
	size_t	len;
	size_t	i;
	char	*line;

	len = 0;
	while (memory[len] && memory[len] != '\n')
		len++;
	printf("len = %zu\n", len);
	line = calloc(len + 1, sizeof(char));
	// if (!line)
	// 	return (NULL);						//Have to free everything?
	i = 0;
	while (i < len)
	{
		line[i] = memory[i];
		i++;
	}
	if (memory[len] == '\n')
		line[i] = '\n';
	return (line);
}

char	*reset_memory(char *memory)
{
	char 	*temp;
	size_t	i;
	size_t	j;

	temp = ft_strdup(memory);
	free(memory);
	memory = NULL;
	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	memory = calloc((ft_strlen(temp) - i + 1), sizeof(char));
	if (!memory)
	{
		free(temp);					//Have to free anything?
		temp = NULL;
		return (NULL);
	}					
	j = 0;
	while (temp[i])
	{
		memory[j] = temp[i];
		j++;
		i++;
	}
	free(temp);
	return (memory);
}

char	*get_next_line(int fd)
{
	static char *memory;
	char		*buffer;
	char		*line;
	int		red;

	line = NULL;
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	memory = read_until_nl(buffer, memory, fd, &red);
//	printf("RED = %d\n", red);
	if (red == 0 && !*memory)
	{
		free(memory);
		return (NULL);
	}
	printf("memory = |%s|\n", memory);
	line = set_line(memory);
	memory = reset_memory(memory);
//	printf("reset memory = |%s|\n", memory);
	return (line);
}