/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:10:10 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/10 14:44:21 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	char	*prefix;
	int		i;

	i = 0;
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	while (data->path[i])
	{
		prefix = ft_strjoin(data->path[i], "/");
		cmdpath = ft_strjoin(prefix, cmd);
		free(prefix);
		if (!access(cmdpath, X_OK))
			return (cmdpath);
		free(cmdpath);
		i++;
	}
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	return (NULL);
}
