/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:01:53 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/14 16:04:21 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_env(t_list *data)
{
	int	i;

	i = 0;
	if (data->path)
	{
		while (data->path[i])
			free (data->path[i++]);
		free (data->path);
		data->path = NULL;
	}
}

void	free_misc(t_list *data)
{
	int	i;

	i = 0;
	if (data->fdpipe)
	{
		while (i < data->nbcomm - 1)
			free(data->fdpipe[i++]);
		free(data->fdpipe);
		data->fdpipe = NULL;
	}
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
}

int	check_files(char *input, char *output)
{
	if (access(input, F_OK) == -1)
	{
		perror("No input file");
		exit(EXIT_FAILURE);
	}
	if (!access(input, F_OK) && access(input, R_OK))
	{
		perror("Permission denied");
		exit(EXIT_FAILURE);
	}
	if (!access(output, F_OK) && access(output, W_OK))
	{
		perror("Permission denied");
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	execprghelper(t_list *data, int i)
{
	if (i == 0)
		firstcmd(data, i);
	else if (i == data->nbcomm - 1)
		lastcmd(data, i);
	else
	{
		close(data->fdpipe[i - 1][1]);
		close(data->fdpipe[i][0]);
		if (dup2(data->fdpipe[i - 1][0], 0) == -1)
			return (perror("no dup"), close(data->fdpipe[i - 1][0]), exit(1));
		if (dup2(data->fdpipe[i][1], 1) == -1)
			return (perror("no dup"), close(data->fdpipe[i][1]), exit(1));
	}
	close(data->fd1);
	close(data->fd2);
	while (i < data->nbcomm - 1)
	{
		close(data->fdpipe[i][0]);
		close(data->fdpipe[i][1]);
		i++;
	}
}

int	parsing(t_list *data, char **argv, char **envp)
{
	int		parameters;
	char	*env_path;

	env_path = find_envp(envp);
	if (!env_path)
		return (perror("Error in finding the PATH"), exit(1), 1);
	data->path = ft_split(env_path, ':');
	free(env_path);
	if (!data->path)
		return (perror("Error in splitting the PATH"), exit(1), 1);
	data->commands = malloc(sizeof(char **) * data->nbcomm + 1);
	if (!data->commands)
		return (1);
	parameters = count_params(data);
	init_comms(data, argv, parameters);
	data->cmdpaths = malloc(sizeof(char *) * data->nbcomm + 1);
	if (!data->cmdpaths)
		return (1);
	if (ft_data(data))
		return (1);
	return (0);
}
