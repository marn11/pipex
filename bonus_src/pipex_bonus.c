/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:02:20 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/12 11:22:10 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void openfiles(int argc, char **argv, t_list *data)
{
	if (data->heredoc_flag)
	{
		handle_heredoc(data);
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
		//free everything needed
		exit(EXIT_FAILURE);
	}
}

int ft_data(t_list *data)
{
	int	i;

	i = 0;
	data->fdpipe = malloc(sizeof(int *) * (data->nbcomm - 1));
	if (!data->fdpipe)
		return (free(data->cmdpaths),ft_free_envpath(data), ft_free_cmd(data),1);
	while (i < data->nbcomm)
	{
		if (data->commands[i][0])
			data->cmdpaths[i] = get_cmd_path(data, data->commands[i][0]);
		else
			data->cmdpaths[i] = NULL;
		i++;
	}
	return (0);
}

int	parsing(t_list *data, char **argv, char **envp)
{
	int		i;
	int		paramaters;

	i = 0;
	data->path = ft_split(find_envp(envp), ':');
	if (!data->path)
		return (perror("Error in finding the PATH"), 1);
	data->commands = malloc(sizeof(char **) * data->nbcomm + 1);
	if (!data->commands)
		return (ft_free_envpath(data), 1);
	if (data->heredoc_flag)
		paramaters = 3;
	else
		paramaters = 2;
	while (i < data->nbcomm)
	{
		data->commands[i] = ft_split2(argv[i + paramaters]);
		i++;
	}
	data->cmdpaths = malloc(sizeof(char *) * data->nbcomm + 1);
	if (!data->cmdpaths)
		return (ft_free_envpath(data), ft_free_cmd(data), 1);
	if (ft_data(data))
		return (1);
	return (0);
}//checki l epxlanation d multiple commands f here doc w checki dik second if condition 

void	execprghelper(t_list *data, int i)
{
	if (i == 0)
	{
		close(data->fdpipe[i][0]);
		dup2(data->fd1, 0);
		dup2(data->fdpipe[i][1], 1);
	}
	else if (i == data->nbcomm - 1)
	{
		close(data->fdpipe[i - 1][1]);
		dup2(data->fdpipe[i - 1][0], 0);
		dup2(data->fd2, 1);
	}
	else
	{
		close(data->fdpipe[i - 1][1]);
		close(data->fdpipe[i][0]);
		dup2(data->fdpipe[i - 1][0], 0);//dup needs protection
		dup2(data->fdpipe[i][1], 1);
	}
	close(data->fd1);
	close(data->fd2);
	while (i < data->nbcomm - 1)
	{
		close(data->fdpipe[i][0]);
		close(data->fdpipe[i][1]);
		i++;
	}
}
void	parent_close(t_list *data, int i)
{
	if (!i)
	{
		close(data->fdpipe[i][1]);
		close(data->fd1);
	}
	else if (i == data->nbcomm - 1)
	{
		close(data->fdpipe[i - 1][0]);
		close(data->fd2);
	}
	else
	{
		close(data->fdpipe[i - 1][0]);
		close(data->fdpipe[i][1]);
	}//they should be closed in the parent process and the child process because the fds get dupped too
}

void	execprg(t_list *data, int i, char **envp)
{
	execprghelper(data, i);
	int fd = 2;
	dprintf(fd, "%s >>>>>>>>>>> %s\n", data->cmdpaths[i], data->commands[i][0]);
	execve(data->cmdpaths[i], data->commands[i], envp);
	if (data->cmdpaths[i])
	{
		if (!access(data->cmdpaths[i], X_OK))
		{
			perror("File not executable");
			//free kolchi
			exit(EXIT_FAILURE);
		}
		perror("pipex: command is found but is not executable");
		//free kolchi
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("pipex: command not found");
		//free kolchi
		exit(EXIT_FAILURE);
	}
}

int check_files(char *input, char *output)
{
	if (access(input, F_OK) == -1)
	{
		perror("No input file");
		exit(EXIT_FAILURE);
	}
	if (!access(input, F_OK) && access(input, R_OK))
	{
		perror("Permission denied");
		exit(EXIT_FAILURE);
	}
	if (!access(output, F_OK) && access(output, W_OK))
	{
		perror("Permission denied");
		exit(EXIT_FAILURE);
	}
	return (0);
}

void usage_check(int argc, char **argv, char **envp, t_list *data)
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
	//check_files(argv[1], argv[argc - 1]);
	if (parsing(data, argv, envp))
		exit(EXIT_FAILURE);	
}
void createpipes(t_list *data)
{
	int	i;

	i = 0;
	while (i < data->nbcomm - 1)
	{
		data->fdpipe[i] = malloc(sizeof (int) * 2);
		if (!data->fdpipe[i])
		{
			//free everything
			exit(EXIT_FAILURE);
		}
		if (pipe(data->fdpipe[i]) == -1)
		{
			//free everything
			exit(EXIT_FAILURE);
		}
		i++;
	}
	data->pid = malloc(sizeof (pid_t) * (data->nbcomm));
	if (!data->pid)
	{
		//free everything
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv, char **envp)
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
		{
			perror("No child :/");
			//free everything
			exit(EXIT_FAILURE);
		}
		if (data.pid[i] == 0)
			execprg(&data,i, envp);
		else
			parent_close(&data, i);
		i++;
	}
	while (i > 0)
	{
		i--;
		waitpid(data.pid[i], NULL, 0);
	}
	//free kolchi
}
