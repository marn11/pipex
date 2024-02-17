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
		{
			if(data->fdpipe)
				free(data->fdpipe[i++]);
			else
				i++;
		}
		free(data->fdpipe);
		data->fdpipe =  NULL;
		if(data->pid)
		{
			free(data->pid);
			data->pid = NULL;
		}
	}
}

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
			{
				printf("free data->commands[i][j]\n");
				free (data->commands[i][j++]);
			}
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
		dup2(data->fdpipe[i - 1][0], 0);
		dup2(data->fdpipe[i][1], 1);
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

void cleanup(t_list *data) {
    free_cmd(data);
    free_env(data);
    free_misc(data);
}

int	parsing(t_list *data, char **argv, char **envp)
{
	int		i;
	int		paramaters;
	char	*env_path;

	i = 0;
	env_path = find_envp(envp);
	if (!env_path)
		return (perror("Error in finding the PATH"), 1);
	data->path = ft_split(env_path, ':');
	free(env_path);
	if (!data->path)
		return (perror("Error in splitting the PATH"), 1);
	data->commands = malloc(sizeof(char **) * data->nbcomm + 1);
	if (!data->commands)
		return (1);
	if (data->heredoc_flag)
		paramaters = 3;
	else
		paramaters = 2;
	while (i < data->nbcomm)
	{
		data->commands[i] = ft_split2(argv[i + paramaters]);
		i++;
	}
	data->cmdpaths = malloc(sizeof(char *) * data->nbcomm + 1);
	if (!data->cmdpaths)
		return (1);
	if (ft_data(data))
		return (1);
	return (0);
}

