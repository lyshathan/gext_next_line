/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:32:40 by lthan             #+#    #+#             */
/*   Updated: 2024/11/19 14:54:48 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main (int arc, char **arv)
{
	(void)arc;
	char	*filename = arv[1];
	char	*line = NULL;
	int fd = open(filename, O_RDWR);

	if(fd == -1)
		exit(1);

	int i = 1;
	while ((line = get_next_line(fd)) && i < 10)
	{
		printf("line %d ------> ||%s||\n\n", i, line);
		free(line);
		i++;
	}
	// line = get_next_line(fd);
	// printf("line %d ------> ||%s||\n\n", i, line);
	// free(line);

	close(fd);
	return (0);
}