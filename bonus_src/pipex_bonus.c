/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:02:20 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/14 10:56:13 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	openfiles(int argc, char **argv, t_list *data)
{
	if (data->heredoc_flag)
	{
		init(data);
		data->fd1 = open(".tmp.txt", O_RDONLY);
		if (data->fd1 == -1)
		{
			perror("Error in opening the input file");
			exit(EXIT_FAILURE);
		}
		data->fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		data->fd1 = open(argv[1], O_RDONLY);
		data->fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (data->fd2 == -1)
	{
		perror("Error in opening the output file");
		exit(EXIT_FAILURE);
	}
}

void	execprg(t_list *data, int i, char **envp)
{
	execprghelper(data, i);
	execve(data->cmdpaths[i], data->commands[i], envp);
	if (data->cmdpaths[i])
	{
		if (!access(data->cmdpaths[i], X_OK))
		{
			perror("File not executable");
			exit(EXIT_FAILURE);
		}
		perror("pipex: command is found but is not executable");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("pipex: command not found");
		exit(EXIT_FAILURE);
	}
}

void	usage_check(int argc, char **argv, char **envp, t_list *data)
{
	int	i;

	i = 0;
	data->heredoc_flag = 0;
	data->nbcomm = argc - 3;
	if (argc < 5)
	{
		perror("Error in arguments");
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		data->heredoc_flag = 1;
		data->limiter = argv[2];
		data->nbcomm = argc - 4;
		here_doc_data(argc, argv, envp, data);
	}
	if (!data->heredoc_flag)
	{
		check_files(argv[1], argv[argc - 1]);
	}
	if (parsing(data, argv, envp))
		exit(EXIT_FAILURE);
}

void	createpipes(t_list *data)
{
	int	i;

	i = 0;
	while (i < data->nbcomm - 1)
	{
		data->fdpipe[i] = malloc(sizeof (int) * 2);
		if (!data->fdpipe[i])
		{
			exit(EXIT_FAILURE);
		}
		if (pipe(data->fdpipe[i]) == -1)
		{
			exit(EXIT_FAILURE);
		}
		i++;
	}
	data->pid = malloc(sizeof (pid_t) * (data->nbcomm));
	if (!data->pid)
	{
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	data;
	int		i;

	i = 0;
	usage_check(argc, argv, envp, &data);
	openfiles(argc, argv, &data);
	createpipes(&data);
	while (i < data.nbcomm)
	{
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			perror("No child :/");
		if (data.pid[i] == 0)
			execprg(&data, i, envp);
		else
			parent_close(&data, i);
		i++;
	}
	while (i > 0)
	{
		i--;
		waitpid(data.pid[i], NULL, 0);
	}
	unlink(".tmp.txt");
}
