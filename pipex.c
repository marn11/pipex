/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:46:32 by mbenchel          #+#    #+#             */
/*   Updated: 2024/01/26 00:22:56 by mbenchel         ###   ########.fr       */
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
void execcomm(const char *cmd_path, char **cmd_args, char **envp)
{
	pid_t	pid;
	int		fd_io[2];

	pipe(fd_io);
	pid = fork();
	if (pid == -1)
	{
		perror("Failed forking");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
	
		dup2(fd_io[0], STDIN_FILENO);
		close(fd_io[0]);
		dup2(fd_io[1], STDOUT_FILENO);
		close(fd_io[1]);

		int i = 0;
		while(cmd_args[i] != NULL)
		{
			printf("%s ", cmd_args[i]);
			i++;
		}
		printf("\n");
		
		execve(cmd_path, cmd_args, envp);
	}
	else
	{
		close (fd_io[0]);
		close (fd_io[1]);
		waitpid(pid, NULL, 0); // change this later to null as i dont need the exit status

	}
}
int main(int argc, char *argv[], char **envp)
{
    (void)argc;
    (void)argv;


    char *cmd_path = "ls";
    char *cmd_args[] = {"ls", "-l", NULL};
	char *cmd = get_cmd_path(cmd_path, envp);
    execcomm(cmd, cmd_args, envp);// wslt hna and this is not working 

    return 0;
}
