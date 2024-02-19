/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:15:33 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/14 14:04:05 by mbenchel         ###   ########.fr       */
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
	int		fd1;
	int		fd2;
	int		**fdpipe;
	char	**cmdpaths;
	char	**path;
	int		nbcomm;
	char	*limiter;
	char	***commands;
	int		heredoc_flag;
	pid_t	*pid;
}	t_list;

int		execprg(t_list *data, int i, char **envp);
int		parsing(t_list *data, char **argv, char **envp);
char	*find_envp(char **envp);
char	*get_cmd_path(t_list *data, char *cmd);
void	free_env(t_list *data);
void	free_cmd(t_list *data);
int		openfiles(int argc, char **argv, t_list *data);
int		createpipes(t_list *data);
void	here_doc_data(int argc, char **argv, char **envp, t_list *data);
int		ft_data(t_list *data);
void	handle_heredoc(t_list *data, int fd, int fd1);
void	init(t_list *data);
int		check_files(char *input, char *output);
void	execprghelper(t_list *data, int i);
int		parsing(t_list *data, char **argv, char **envp);
void	parent_close(t_list *data, int i);
int		ft_data(t_list *data);
void	firstcmd(t_list *data, int i);
void	lastcmd(t_list *data, int i);
void	free_misc(t_list *data);
void	cleanup(t_list *data);
int		count_params(t_list *data);
void	init_comms(t_list *data, char **argv, int parameters);

#endif