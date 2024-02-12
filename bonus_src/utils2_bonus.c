/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:01:53 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/08 18:26:51 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_envpath(t_list *data)
{
	int	i;

	i = 0;
	while(data->path[i])
		free(data->path[i++]);
	free(data->path);
}
void	ft_free_cmd(t_list *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nbcomm)
	{
		j = 0;
		while(data->commands[i][j])
			free(data->commands[i][j++]);
		free(data->commands[i]);
		i++;
	}
	free(data->commands);
}
