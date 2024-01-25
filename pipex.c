/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:46:32 by mbenchel          #+#    #+#             */
/*   Updated: 2024/01/25 15:20:32 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_cmd_path(const char *cmd, char **envp)
{
	char	*fullpath;
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
		fullpath = ft_strnstr(envp[i], "PATH=", 5);
		if (fullpath)
		{
			fullpath = ft_substr(fullpath, 5, ft_strlen(fullpath));
			break ;
		}
		i++;
	}
	paths = ft_split(fullpath, ':');
	if (!paths)
	{
		free(fullpath);
		return (NULL);
	}
	j = 0;
	while (paths[j])
	{
		tmp = paths[j];
		paths[j] = ft_strjoin(paths[j], "/");
		free(tmp); // free the memory allocated to paths + j before we appended the /
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
	//free(fullpath);
	l = 0;
	while (paths[l])
	{
		free(paths[l]);
		l++;
	}
	free(paths);
	return (NULL);
}
