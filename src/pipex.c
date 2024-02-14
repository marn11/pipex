/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:33:38 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/14 02:39:46 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	firstcmd(t_list *data, char **envp)
{
	data->cmd1path = get_cmd_path(data, *data->cmd1);
	if (data->cmd1path == NULL)
	{
		perror("Where is the first command?");
		exit(EXIT_FAILURE);
	}
	dup2(data->fd1, 0);
	close(data->fd1);
	dup2(data->fd[1], 1);
	close(data->fd[0]);
	close(data->fd[1]);
	if (execve(data->cmd1path, data->cmd1, envp) == -1)
	{
		perror("Error in execution");
		exit(EXIT_FAILURE);
	}
}

void	secondcmd(t_list *data, char **envp)
{
	data->cmd2path = get_cmd_path(data, *data->cmd2);
	if (data->cmd2path == NULL)
	{
		perror("Where is the second command?");
		exit(EXIT_FAILURE);
	}
	dup2(data->fd2, 1);
	close(data->fd2);
	dup2(data->fd[0], 0);
	close(data->fd[1]);
	close(data->fd[0]);
	if (execve(data->cmd2path, data->cmd2, envp) == -1)
	{
		perror("Error in execution");
		exit(EXIT_FAILURE);
	}
}
// check for leaks + protections carefully

void	parsing(t_list *data, char **argv, char **envp)
{
	char	*cmdtmp;

	data->input = ft_strdup(argv[1]);
	data->output = ft_strdup(argv[4]);
	cmdtmp = ft_strdup(argv[2]);
	data->cmd1 = ft_split1(cmdtmp);
	free(cmdtmp);
	cmdtmp = ft_strdup(argv[3]);
	data->cmd2 = ft_split1(cmdtmp);
	free(cmdtmp);
	data->path = ft_split(find_envp(envp), ':');
	if (!data->path)
	{
		perror("Environment error");
		exit(EXIT_FAILURE);
	}
}

void	execprg(t_list *data, char **envp)
{
	int	pid;

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
		firstcmd(data, envp);
	else
	{
		if (waitpid(pid, NULL, 0) == pid)
			secondcmd(data, envp);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_list	data;

	if (argc == 5)
	{
		parsing(&data, argv, envp);
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
	else
		perror("ghi glbha ofppt");
	exit(EXIT_FAILURE);
}
