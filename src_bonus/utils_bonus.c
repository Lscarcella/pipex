/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/24 16:00:03 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	init_struct(int argc, char **argv, char **envp, t_pipex *pipex)
{
	ft_memset(&pipex->data, 0, sizeof(pipex->data));
	ft_memset(&pipex->files, 0, sizeof(pipex->files));
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	has_heredoc(pipex);
	pipex->data.cmd_nbr = (argc - 3) - pipex->data.has_heredoc;
	pipex->data.pipe_nbr = 2 * (pipex->data.cmd_nbr - 1);
	pipex->data.argv_len = ft_strlen(pipex->argv[2]);
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
