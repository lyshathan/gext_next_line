/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_lines_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:28:46 by lthan             #+#    #+#             */
/*   Updated: 2024/11/19 13:15:10 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;
	char	*str;

	if (!s)
		return (0);
	i = 0;
	str = (char *)s;
	while (str[i])
	{
		i++;
	}
	return (i);
}
char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (((char *)s)[i])
	{
		if (((char *)s)[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if (((char *)s)[i] == 0 && (char)c == 0)
		return (&((char *)s)[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	len = ft_strlen((char *)s);
	str = malloc ((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (((char *)s)[i])
	{
		str[i] = ((char *)s)[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
	return ;
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
		return (ft_strdup(s1));
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (((char *)s1)[++i])
		str[i] = ((char *)s1)[i];
	j = 0;
	while (((char *)s2)[j])
	{
		str[i] = ((char *)s2)[j];
		i++;
		j++;
	}
	return (str);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	if ((size != 0 && nmemb > SIZE_MAX / size)
		|| (nmemb != 0 && size > SIZE_MAX / nmemb))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}