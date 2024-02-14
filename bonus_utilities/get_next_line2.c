/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:16:06 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/12 15:25:22 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line2.h"

size_t	ft_strlen_nl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\n')
		i++;
	return (i);
}

char	*ft_read(char *block, int fd, int *n)
{
	char	*buffer;
	char	*res;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (block);
	*n = read(fd, buffer, BUFFER_SIZE);
	if (*n == -1)
		res = NULL;
	else if (*n > 0)
	{
		buffer[*n] = '\0';
		res = ft_strjoin(block, buffer);
	}
	else
	{
		res = ft_strdup(block);
	}
	free(buffer);
	if (res)
	{
		if (res[0] == '\0')
			return (free(res), NULL);
	}
	return (res);
}

char	*ft_free(char **block, int len, int null)
{
	char	*l;

	l = ft_substr(*block, 0, len);
	free(*block);
	if (null)
		*block = NULL;
	return (l);
}

char	*get_next_line(int fd)
{
	static char	*block;
	int			n;
	int			llen;
	char		*block_before;

	n = 0;
	while (fd >= 0 && fd <= OPEN_MAX && BUFFER_SIZE > 0
		&& BUFFER_SIZE <= INT_MAX && n >= 0)
	{
		block_before = block;
		if (ft_strchr(block, '\n'))
		{
			llen = ft_strlen_nl(block) + 1;
			block = ft_substr(block_before, llen, 0);
			return (ft_free(&block_before, llen, 0));
		}
		else
		{
			block = ft_read(block_before, fd, &n);
			free(block_before);
			if (n == 0)
				return (ft_free(&block, 0, 1));
		}
	}
	return (NULL);
}
