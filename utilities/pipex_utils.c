/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 02:39:27 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/01 18:18:35 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!big && !len)
		return (0);
	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
			{
				return ((char *)&big[i]);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*c;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (s == NULL || start >= slen)
		return (ft_strdup(""));
	if (start + len > slen)
		len = slen - start;
	c = (char *)malloc((len + 1) * sizeof(char));
	if (c == NULL)
		return (NULL);
	ft_strlcpy(c, &s[start], len + 1);
	return (c);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*c;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	c = malloc(len + 1);
	if (!c)
		return (NULL);
	while (s1[j])
		c[i++] = s1[j++];
	j = 0;
	while (s2[j])
		c[i++] = s2[j++];
	c[i] = '\0';
	return (c);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
