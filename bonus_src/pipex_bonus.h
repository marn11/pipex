/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:15:33 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/11 20:55:19 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../bonus_utilities/utilities2.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <stddef.h>

typedef struct s_data
{
	int		fds2[2];
	int		fd[2];
	int		fd1;
	int		fd2;
	int		**fdpipe;
	char	**cmdpaths;
	char	*input;
	char	*output;
	char	**path;
	char	*cmd1path;
	char	*lastcmdpath;
	int		nbcomm;
	char	*limiter;
	char	***commands;
	char	*cmdpath;
	int		heredoc_flag;
	pid_t	*pid;
}	t_list;

void	execprg(t_list *data, int i, char **envp);
int		parsing(t_list *data, char **argv, char **envp);
char	*find_envp(char **envp);
char	*get_cmd_path(t_list *data, char *cmd);
void	ft_free_envpath(t_list *data);
void	ft_free_cmd(t_list *data);
void	openfiles(int argc, char **argv, t_list *data);
void	createpipes(t_list *data);
void	here_doc_data(int argc, char **argv, char **envp, t_list *data);
int		ft_data(t_list *data);
void	handle_heredoc(t_list *data);


//remove functions that are only in one file
#endif