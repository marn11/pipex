/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:10:10 by mbenchel          #+#    #+#             */
/*   Updated: 2024/01/31 15:47:48 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_envp(char **envp)
{
	int		i;
	char	*fullpath;
	
	i = 0;
	fullpath = NULL;
	while(envp[i] && envp[i][0] != '\0')
	{
		fullpath = ft_strnstr(envp[i], "PATH=", 5);
		if (fullpath)
			return (ft_substr(fullpath, 5, ft_strlen(fullpath))); // to avoid reassigning fullpath 
		i++;
	}
		return (NULL);
}

char	*get_cmd_path(t_list *data, char *cmd)
{
	char	*cmdpath;
	char	*tmp;
	int		i;

	i = 0;
	while (data->path[i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		cmdpath = ft_strjoin(tmp, cmd);
		if (!access(cmdpath, X_OK))
		{
			free(tmp);
			return(cmdpath);
		}
		free(tmp);
		free(cmdpath);
		i++;
	}
	if (!access(cmd, X_OK))
		return (cmd);
	return (NULL);
}
