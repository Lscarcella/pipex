/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/24 14:35:14 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	init_struct(int argc, char **argv, char **envp, t_pipex *pipex)
{
	ft_memset(&pipex->data, 0, sizeof(pipex->data));
	ft_memset(&pipex->files, 0, sizeof(pipex->files));
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->data.env_path = get_path(envp);
}

char	*get_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}

void	get_cmd(t_pipex *pipex, char *cmd_arg)
{
	pipex->data.cmd_tab = ft_split(cmd_arg, ' ');
	if (pipex->data.cmd_tab == NULL)
	{
		printf("empty cmd");
		exit(EXIT_FAILURE);
	}
	build_cmd(pipex);
}

void	build_cmd(t_pipex *pipex)
{
	char	**path_tab;
	char	*cmd_path;
	int		i;

	i = 0;
	path_tab = ft_split(pipex->data.env_path, ':');
	while (path_tab[i])
	{
		path_tab[i] = ft_strjoin(path_tab[i], "/");
		cmd_path = ft_strjoin_no_free(path_tab[i], pipex->data.cmd_tab[0]);
		if (access(cmd_path, X_OK) == 0)
		{
			free_tab(path_tab);
			pipex->data.cmd_path = cmd_path;
			return ;
		}
		free(cmd_path);
		i++;
	}
	free_tab(path_tab);
	error_while_building(pipex);
}
