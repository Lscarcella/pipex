/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/06/22 10:32:08 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void init_struct(int argc, char **argv, char **envp, t_pipex *pipex)
{
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	has_heredoc(pipex);
	if(pipex->data.has_heredoc == TRUE)
		pipex->data.arg_pos = 3;
	else
		pipex->data.arg_pos = 2;
	pipex->data.cmd_nbr = (argc - 3) - pipex->data.has_heredoc;
	pipex->data.pipe_nbr = 2 * (pipex->data.cmd_nbr - 1);
	pipex->data.argv_len = ft_strlen(pipex->argv[2]);
	pipex->data.env_path = get_path(envp);
}

void	has_heredoc(t_pipex *pipex)
{
	size_t	len;

	len = ft_strlen(pipex->argv[1]);
	if (ft_strncmp(pipex->argv[1], "here_doc", len) == 0)
		pipex->data.has_heredoc = 1;
	else
		pipex->data.has_heredoc = 0;
}


char	*ft_join(char *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*newstring;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newstring = malloc((s1len + s2len) + 1);
	ft_strlcpy(newstring, s1, s1len + 1);
	ft_strlcat(newstring, s2, s1len + s2len + 1);
	return (newstring);
}
char	*get_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}