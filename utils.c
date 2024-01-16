/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:20:37 by mbenchel          #+#    #+#             */
/*   Updated: 2024/01/16 17:20:54 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s)
{
	size_t	l;
	size_t	j;
	char	*dup;

	j = 0;
	l = ft_strlen(s);
	dup = malloc(sizeof(char) * (l + 1));
	if (dup == NULL)
		return (NULL);
	while (j < l)
	{
		dup[j] = s[j];
		j++;
	}
	dup[l] = '\0';
	return (dup);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (size > i + 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}