/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:02:38 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/12 13:36:04 by mbenchel         ###   ########.fr       */
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
void	here_doc_data(int argc, char **argv, char **envp, t_list *data)
{
	if (argc < 6)
	{
		perror("here_doc not used correctly");
		exit(EXIT_FAILURE);
	}
	if (parsing(data, argv, envp))
		exit(EXIT_FAILURE);
}

void	handle_heredoc(t_list *data)
{
	int		fd;
	int		fd1;
	char 	*line;
	char	*tmp;

	fd = open(".tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error in opening the temporary file");
		exit(EXIT_FAILURE);
	}
	fd1 = dup(STDIN_FILENO);
	line = NULL;
	tmp = ft_strjoin(data->limiter, "\n");
	while(1)
	{
		write(1, "here_doc > ", 11);
		line = get_next_line(fd1);
		printf("line = %s\n", line);
		if (!line)
		{
			close (fd);
			break;
		}
		if (!ft_strncmp(line, tmp, ft_strlen(tmp) + 1))
		{
			close (fd);
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line) - 1);
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}
