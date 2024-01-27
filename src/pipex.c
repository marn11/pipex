/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:46:32 by mbenchel          #+#    #+#             */
/*   Updated: 2024/01/27 20:47:47 by mbenchel         ###   ########.fr       */
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
		{
			fullpath = ft_substr(fullpath, 5, ft_strlen(fullpath));
			break ;
		}
		i++;
	}
		return (fullpath);
}

void	parsing(t_list *data, char **argv, char **envp)
{
	char	*cmdtmp;
	char	*envpath;
	
	data->input = ft_strdup(argv[1]);
	data->output = ft_strdup(argv[4]);
	cmdtmp = ft_strdup(argv[2]);
	data->cmd1 = ft_split(cmdtmp, ' ');
	free(cmdtmp);
	cmdtmp = ft_strdup(argv[3]);
	data->cmd2 = ft_split(cmdtmp, ' ');
	free(cmdtmp);
	envpath = find_envp(envp);
	if (envpath == NULL)
	{
		perror("Environment error");
		exit(0);
	}
	data->path = ft_split(envpath, ':');
	free(envpath);
}

int main(int argc, char *argv[], char **envp)
{
	t_list	data;

	if (argc == 5)
	{
		parsing(&data, argv, envp);
		if ((data.fd1 = open(data.input, O_RDWR)) < 0)
			return(perror("Input file doesn't exist"));
		if ((data.fd2 = open(data.output, O_RDWR | O_CREAT | O_TRUNC)) < 0)
				return(perror("Output file doesn't exist"));
	
	}
	else
		perror("wa333333333");
}

