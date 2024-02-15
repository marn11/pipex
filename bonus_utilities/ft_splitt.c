/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:25:58 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/12 15:25:14 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities2.h"

static int	whitespace(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

static size_t	countwords(const char *s)
{
	size_t	i;
	size_t	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] && whitespace(s[i]))
			i++;
		if (s[i])
			wc++;
		while (s[i] && !whitespace(s[i]))
			i++;
	}
	return (wc);
}

static char	**freemem(char **s)
{
	int	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i])
		{
			free(s[i]);
			i++;
		}
		free(s);
	}
	return (NULL);
}

static	char	*getwords(int *i, const char *s)
{
	int		wordsz;
	int		tpos;
	int		j;
	char	*res;

	j = 0;
	while (s[*i] && whitespace(s[*i]))
		(*i)++;
	tpos = *i;
	while (s[*i] && !whitespace(s[*i]))
		(*i)++;
	wordsz = *i - tpos;
	res = (char *)malloc((wordsz + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (tpos + j < *i)
	{
		res[j] = s[tpos + j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	**ft_split2(char const *s)
{
	char	**res;
	int		wc;
	int		j;
	int		i;

	if (s == NULL)
		return (NULL);
	j = 0;
	i = 0;
	wc = countwords(s);
	res = (char **)malloc((wc + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	while (j < wc)
	{
		res[j] = getwords(&i, s);
		if (res[j] == NULL)
			return (freemem(res));
		j++;
	}
	res[wc] = NULL;
	return (res);
}
