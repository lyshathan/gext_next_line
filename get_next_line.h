/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:28:44 by lthan             #+#    #+#             */
/*   Updated: 2024/11/25 15:49:46 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10000000
#endif

// #define RED     "\033[1;31m"
// #define GREEN   "\033[1;32m"
// #define YELLOW  "\033[1;33m"
// #define BLUE    "\033[1;34m"
// #define RESET   "\033[0m"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

#endif