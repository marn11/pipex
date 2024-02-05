/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:15:33 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/05 15:38:40 by mbenchel         ###   ########.fr       */
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
	int		fds[2];
	int		fds2[2];
	int		fd[2];
	int		fd1;
	int		fd2;
	char	*input;
	char	*output;
	char	**path;
	char	*cmd1path;
	char	*lastcmdpath;
	int		nbcomm;
	char	*limiter;
	char	***commands;
	char	*cmdpath;
}	t_list;
void	execprg(t_list *data, char **envp);
void	lastcmd(t_list *data, char **envp);
void	firstcmd(t_list *data, char **envp);
void	parsing(t_list *data, int argc, char **argv, char **envp);
char	*find_envp(char **envp);
char	*get_cmd_path(t_list *data, char *cmd);
void midcmds(t_list *data, char **envp);

#endif