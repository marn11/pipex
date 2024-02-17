/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 02:51:22 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/14 10:45:54 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parent_close(t_list *data, int i)
{
	if (!i)
	{
		close(data->fdpipe[i][1]);
		close(data->fd1);
	}
	else if (i == data->nbcomm - 1)
	{
		close(data->fdpipe[i - 1][0]);
		close(data->fd2);
	}
	else
	{
		close(data->fdpipe[i - 1][0]);
		close(data->fdpipe[i][1]);
	}
}

int	ft_data(t_list *data)
{
	int	i;

	i = 0;
	data->fdpipe = malloc(sizeof(int *) * (data->nbcomm - 1));
	if (!data->fdpipe)
		return (1);
	while (i < data->nbcomm)
	{
		if (data->commands[i][0])
			data->cmdpaths[i] = get_cmd_path(data, data->commands[i][0]);
		else
			data->cmdpaths[i] = NULL;
		if(data->cmdpaths[i] == NULL)
			return (1);
		i++;
		data->cmdpaths[i] = NULL;
	}
	return (0);
}

void	firstcmd(t_list *data, int i)
{
	close(data->fdpipe[i][0]);
	dup2(data->fd1, 0);
	dup2(data->fdpipe[i][1], 1);
}

void	lastcmd(t_list *data, int i)
{
	close (data->fdpipe[i - 1][1]);
	dup2(data->fdpipe[i - 1][0], 0);
	dup2(data->fd2, 1);
}
