/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/06/04 17:07:07 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void init_struct(int argc, char **argv, char **envp, t_data *data)
{
	ft_memset(data, 0, sizeof(*data));
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	has_heredoc(data);
	if(data->has_heredoc == TRUE)
		data->arg_pos == 2;
	else
		data->arg_pos == 1;
	data->cmd_nbr = (argc - 3) - data->has_heredoc;
	data->pipe_nbr = 2 * (data->cmd_nbr - 1);
	data->argv_len = ft_strlen(data->argv[2]);
	data->env_path = get_path(envp);
}

void	has_heredoc(t_data *data)
{
	size_t	len;

	len = ft_strlen(data->argv[1]);
	if (ft_strncmp(data->argv[1], "here_doc", len) == 0)
		data->has_heredoc = 1;
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
