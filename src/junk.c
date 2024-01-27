// char *get_cmd_path(const char *cmd, char **envp)
// {
// 	char	**paths;
// 	char	*cmdpath;
// 	char	*tmp;
// 	int		j;
// 	int		k;
// 	int		l;

// 	paths = ft_split(fullpath, ':');
// 	if (!paths)
// 	{
// 		free(fullpath);
// 		return (NULL);
// 	}
// 	j = 0;
// 	while (paths[j])
// 	{
// 		tmp = paths[j];
// 		paths[j] = ft_strjoin(paths[j], "/");
// 		free(tmp); // free the memory allocated to paths + j before we appended the /
// 		j++;
// 	}
// 	k = 0;
// 	while(paths[k])
// 	{
// 		cmdpath = ft_strjoin(paths[k], cmd);
// 		if (access(cmdpath, X_OK) == 0)
// 			return (cmdpath);
// 		free (cmdpath);
// 		k++;
// 	}
// 	//free(fullpath);
// 	l = 0;
// 	while (paths[l])
// 	{
// 		free(paths[l]);
// 		l++;
// 	}
// 	free(paths);
// 	return (NULL);
// }
// void execcomm(const char *cmd_path, char **cmd_args, char **envp)
// {
// 	pid_t	pid;
// 	int		fd_io[2];

// 	pipe(fd_io);
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("Failed forking");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 	{
	
// 		close(fd_io[0]);
// 		dup2(fd_io[1], STDOUT_FILENO);
// 		close(fd_io[1]);

// 		int i = 0;
// 		while(cmd_args[i] != NULL)
// 		{
// 			printf("%s ", cmd_args[i]);
// 			i++;
// 		}
// 		printf("\n");
// 		execve(cmd_path, cmd_args, envp);
// 		perror("Error in execution");
//         exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		close (fd_io[1]);
// 		waitpid(pid, NULL, 0);
// 	}
// }