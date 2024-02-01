/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:15:33 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/01 18:15:36 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../utilities/utilities.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <stddef.h>

typedef struct s_data
{
	int		fd[2];
	int		fd1;
	int		fd2;
	char	*input;
	char	*output;
	char	**cmd1;
	char	**cmd2;
	char	**path;
	char	*cmd1path;
	char	*cmd2path;
}	t_list;
char	*find_envp(char **envp);
void	parsing(t_list *data, char **argv, char **envp);
void	execprg(t_list *data, char **envp);
void	firstcmd(t_list *data, char **envp);
char	*get_cmd_path(t_list *data, char *cmd);
void	firstcmd(t_list *data, char **envp);
void	secondcmd(t_list *data, char **envp);
#endif