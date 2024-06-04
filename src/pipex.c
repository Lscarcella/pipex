/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/06/04 17:13:39 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex(t_data *data)
{
	pid_t pid;
	int i;
	
	get_cmd(data, data->argv[data->arg_pos]);
	pipe(data->pipe_fd);
	while(data->cmd_nbr > 1)
	{
	pid = fork();
	if (pid == -1)
		error("error : fork returned -1");
	if (pid == 0)
		child(data);
	else
		parent(data, pid);
	data->cmd_nbr--;
	data->arg_pos++;
	}
}

char *get_cmd(t_data *data, char *cmd_arg)
{
	char	*tmp;
	char	**path_tab;
	char	*cmd;
	int		i;
	
	i = 0;
	path_tab = ft_split(data->env_path, ':');
	cmd = ft_join("/", cmd_arg);
	while(path_tab)
	{
		tmp = ft_strjoin(path_tab[i], cmd);
		if(access(tmp, F_OK) == 0)
		{
			data->cmd_path = tmp;
			free(tmp);
			return (0);
		}
		i++;
	}
	error("command not found");
	free(tmp);
	exit(EXIT_FAILURE);
	//fermer tout les fichiers
}
	
void	child(t_data * data)
{
		dup2(data->infile_fd, STDIN_FILENO);
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		execution(data);
}

void	execution(t_data *data)
{
	if(execve(data->cmd_path, &data->argv[data->arg_pos], data->envp) == -1);
	{
		close(data->pipe_fd[1]);
		close(data->pipe_fd[0]);
		error("execve error");
	}
}

void	parent(t_data *data, pid_t pid)
{
			waitpid(pid, NULL, 0);
}