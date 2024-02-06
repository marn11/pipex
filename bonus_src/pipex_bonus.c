/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:02:20 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/06 17:17:57 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parsing(t_list *data, int argc, char **argv, char **envp)
{
	char	*envpath;
	int		i;

	i = 0;
	data->input = ft_strdup(argv[1]);
	data->output = ft_strdup(argv[argc - 1]);
	data->nbcomm = argc - 3;
	data->commands = malloc(sizeof(char **) * data->nbcomm + 1);
	while (i < data->nbcomm)
	{
		data->commands[i] = ft_split(argv[i + 2], ' ');
		i++;
	}
	data->commands[i] = NULL;
	envpath = find_envp(envp);
	if (envpath == NULL)
	{
		perror("Error in finding the PATH");
		exit(EXIT_FAILURE);
	}
	data->path = ft_split(envpath, ':');
	free(envpath);
}
void	firstcmd(t_list *data, char **envp)
{
	data->cmd1path = get_cmd_path(data, *data->commands[0]);
	if (data->cmd1path == NULL)
	{
		perror("Where is the first command?");
		exit(EXIT_FAILURE);
	}
	dup2(data->fd1, 0);
	close(data->fd1);
	dup2(data->fd[1], 1);
	close(data->fd[0]);
	if (execve(data->cmd1path, data->commands[0], envp) == -1)
	{
		perror("Error in execution");
		exit(EXIT_FAILURE);
	}
}
void	lastcmd(t_list *data, char **envp)
{
	data->lastcmdpath = get_cmd_path(data, *data->commands[data->nbcomm - 1]);
	if (data->lastcmdpath == NULL)
	{
		perror("Where is the second command?");
		exit(EXIT_FAILURE);
	}
	dup2(data->fd2, 1);
	close(data->fd2);
	dup2(data->fd[0], 0);
	close(data->fd[1]);
	if (execve(data->lastcmdpath, data->commands[data->nbcomm - 1], envp) == -1)
	{
		perror("Error in execution");
		exit(EXIT_FAILURE);
	}
}
void	execprg(t_list *data, char **envp)
{
	int	pid;
	int	pid2;

	if (pipe(data->fd) == -1)
	{
		perror("No pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("No child :/");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		firstcmd(data, envp);
		// close(data->fd[0]);
		// close(data->fd[1]);
		exit(EXIT_SUCCESS);
	}
	midcmds(data, envp);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("No child :/");
		exit(EXIT_FAILURE);
	}
	else if (pid2 == 0)
	{
		lastcmd(data, envp);
		exit(EXIT_SUCCESS);
	}
	if (waitpid(pid, NULL, 0) == pid)
	{
		if (waitpid(pid2, NULL, 0) == pid2)
			lastcmd(data, envp);
	}
}
int main(int argc, char *argv[], char **envp)
{
	t_list	data;

	if (argc < 5)
	{
		perror("You're not using Pipex correctly!");
		exit(EXIT_FAILURE);
	}
	else
	{
		parsing(&data, argc, argv, envp);
		data.fd1 = open(data.input, O_RDWR);
		if (data.fd1 < 0)
		{
			perror("Input file doesn't exist");
			exit(EXIT_FAILURE);
		}
		data.fd2 = open(data.output, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (data.fd2 < 0)
		{
			perror("Output file doesn't exist");
			exit(EXIT_FAILURE);
		}
		execprg(&data, envp);
	}
}
