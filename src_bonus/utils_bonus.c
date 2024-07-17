/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/17 13:55:27 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void init_struct(int argc, char **argv, char **envp, t_pipex *pipex)
{
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
	char *cmd;
	
	pipex->data.cmd_tab = ft_split(cmd_arg, ' ');
	cmd = pipex->data.cmd_tab[0];
	if (cmd[0] == '\0')
	{
		printf("empty cmd");
		exit(EXIT_FAILURE);
	}
	build_cmd(pipex, cmd);
}

char *build_cmd(t_pipex *pipex, char *cmd)
{
	char	*tmp_str;
	char	**path_tab;
	char	*cmd_path;
	int		i;

	i = 0;
	path_tab = ft_split(pipex->data.env_path, ':');
	while(path_tab[i])
	{
		tmp_str = ft_strjoin(path_tab[i], "/");
		cmd_path = ft_strjoin(tmp_str, cmd);
		if(access(cmd_path, X_OK) == 0)
		{
			pipex->data.cmd_path = cmd_path;
			return (0);
		}
		i++;
	}
	error("Error\nPlease enter a valid command");
	free(cmd_path);	
	free_tab(path_tab);
	exit(EXIT_FAILURE);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	tab[i] = NULL;
}