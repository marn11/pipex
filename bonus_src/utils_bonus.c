/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:02:38 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/05 16:20:32 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_envp(char **envp)
{
	int		i;
	char	*fullpath;

	i = 0;
	fullpath = NULL;
	while (envp[i] && envp[i][0] != '\0')
	{
		fullpath = ft_strnstr(envp[i], "PATH=", 5);
		if (fullpath)
			return (ft_substr(fullpath, 5, ft_strlen(fullpath)));
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_list *data, char *cmd)
{
	char	*cmdpath;
	int		i;

	i = 0;
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	while (data->path[i])
	{
		cmdpath = ft_strjoin(ft_strjoin(data->path[i], "/"), cmd);
		if (!access(cmdpath, X_OK))
			return (cmdpath);
		free(cmdpath);
		i++;
	}
	if (!access(cmd, X_OK))
		return (cmd);
	return (NULL);
}
void midcmds(t_list *data, char **envp)
{
	int	i;
	int	pid;
	
	i = 0;
	while (i < data->nbcomm - 1)
	{
		pipe(data->fds2);
		pid = fork();
		if (pid == 0)
		{
			dup2(data->fds[0], 0);
			close(data->fds[0]);
			close(data->fds[1]);
			dup2(data->fds2[1], 1);
			close(data->fds2[0]);
			close(data->fds2[1]);
			data->cmdpath = get_cmd_path(data, *data->commands[i]);
			if (data->cmdpath == NULL)
			{
				perror("Where is the command?");
				exit(EXIT_FAILURE);
			}
			if (execve(data->cmdpath, data->commands[i], envp) == -1)
			{
				perror("Error in execution");
				exit(EXIT_FAILURE);
			}
		}
		i++;
	}
}
