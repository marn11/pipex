/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 00:11:32 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/19 01:05:23 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_cmd(t_list *data)
{
	int	i;
	int	j;

	i = 0;
	if (data->commands)
	{
		while (i < data->nbcomm)
		{
			j = 0;
			while (data->commands[i][j])
				free (data->commands[i][j++]);
			free (data->commands[i]);
			i++;
		}
		free(data->commands);
		data->commands = NULL;
	}
	if (data->cmdpaths)
	{
		i = 0;
		while (i < data->nbcomm && data->cmdpaths[i])
			free(data->cmdpaths[i++]);
	}
	free(data->cmdpaths);
	data->cmdpaths = NULL;
}

int	count_params(t_list *data)
{
	if (data->heredoc_flag)
		return (3);
	else
		return (2);
}

void	init_comms(t_list *data, char **argv, int parameters)
{
	int	i;

	i = 0;
	while (i < data->nbcomm)
	{
		data->commands[i] = ft_split2(argv[i + parameters]);
		i++;
	}
}
