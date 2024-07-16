/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/16 14:48:01 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

// char	*ft_join(char *s1, char const *s2)
// {
// 	size_t	s1len;
// 	size_t	s2len;
// 	char	*newstring;

// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	s1len = ft_strlen(s1);
// 	s2len = ft_strlen(s2);
// 	newstring = malloc((s1len + s2len) + 1);
// 	ft_strlcpy(newstring, s1, s1len + 1);
// 	ft_strlcat(newstring, s2, s1len + s2len + 1);
// 	return (newstring);
// }

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