/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:01:53 by mbenchel          #+#    #+#             */
/*   Updated: 2024/02/04 19:02:12 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex_bonus.h"

// void	parsing(t_list *data, int argc, char **argv, char **envp)
// {
// 	char	*cmdtmp;
// 	char	*envpath;

// 	if (ft_strncmp("here_doc", argv[1], 9) == 0)
// 	{
// 		data->nbcomm = argc - 4;
// 		data->limiter = ft_strdup(argv[2]);
// 		data->input = NULL;
// 	}
// 	else
// 		data->input = ft_strdup(argv[1]);
// 	data->output = ft_strdup(argv[argc - 1]);
// 	data->nbcomm = argc - 3;
// }

// int main(int argc, char *argv[], char **envp)
// {
// 	t_list	data;
// 	if (argc < 5)
// 	{
// 		perror("You're not using Pipex correctly!");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (argc < 6 && ft_strncmp("here_doc", argv[1], 9))
// 	{
// 		perror("You're not using the here_doc the right way!");
// 		exit(EXIT_FAILURE);
// 	}
// }