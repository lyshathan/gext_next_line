/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:32:40 by lthan             #+#    #+#             */
/*   Updated: 2024/11/25 14:21:39 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main (int arc, char **arv)
{
	printf("coucou");
	(void)arc;
	char	*filename = arv[1];
	char	*line = NULL;
	int fd = open(filename, O_RDWR);

	if(fd == -1)
		exit(1);

	int i = 1;
	while ((line = get_next_line(fd)) && i < 10)
	{
		printf("line %d ------> ||%s||\n", i, line);
		free(line);
		printf("Free alloc at %p		--> line in main\n", line);
		i++;
		printf("\n=========================\n");
	}

	line = get_next_line(fd);
	printf("line %d ------> ||%s||\n", i, line);
	if (line)
	{
		free(line);
		printf("Free alloc at %p		--> line in main\n", line);
	}

	// line = get_next_line(fd);
	// printf("line %d ------> ||%s||\n\n", i++, line);
	// if (line)
	// 	free(line);

	close(fd);
	return (0);
}