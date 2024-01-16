/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:46:32 by mbenchel          #+#    #+#             */
/*   Updated: 2024/01/16 18:00:59 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_cmd_path(const char *cmd, char **envp)
{
	char	*envppath;
	char	**paths;
	char	*cmdpath;
	char	*tmp;
	int		i;
	int		j;
	int		k;
	int		l;
	
	i = 0;
	while(envp[i] && envp[i][0] != '\0')
	{
		envppath = ft_strnstr(envp[i], "PATH=", 5);
		if (envppath)
		{
			envppath = ft_substr(envppath, 5, ft_strlen(envppath));
			break ;
		}
		i++;
	}
	paths = ft_split(envppath, ':');
	if (!paths)
	{
		free(envppath);
		return (NULL);
	}
	j = 0;
	while (paths[j])
	{
		tmp = paths[j];
		paths[j] = ft_strjoin(paths[j], "/");
		free(tmp);
		j++;
	}
	k = 0;
	while(paths[k])
	{
		cmdpath = ft_strjoin(paths[k], cmd);
		if (access(cmdpath, X_OK) == 0)
			return (cmdpath);
		free (cmdpath);
		k++;
	}
	free(envppath);
	l = 0;
	while (paths[l])
	{
		free(paths[l]);
		l++;
	}
	free(paths);
	return (NULL);
}
#include <stdio.h>
int main(int argc, char *argv[], char **envp)
{
	char *cmd_path;
	char *opt[3] = {"ls", "-la", NULL};
	char *cmd = "ls";
	(void)argc;
	(void)argv;
	cmd_path = get_cmd_path(cmd,envp);
	
	if (!cmd_path)
{
    perror("Error finding command path");
    return -1;
}
	execve(cmd_path,opt, envp);
	printf("yes");
	free(cmd_path);
}