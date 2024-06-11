/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/06/11 14:58:33 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipe(t_pipex *pipex)
{
	pid_t pid;
	int i;
	
	get_cmd(pipex, pipex->argv[pipex->data.arg_pos]);
	while(pipex->data.cmd_nbr > 1)
	{
	pipe(pipex->data.pipe_fd);
	pid = fork();
	if (pid == -1)
		error("error : fork returned -1");
	if (pid == 0)
		child(pipex);
	else
		parent(pipex, pid);
	pipex->data.cmd_nbr--;
	pipex->data.arg_pos++;
	}
}

char *get_cmd(t_pipex *pipex, char *cmd_arg)
{
	char	*tmp;
	char	**path_tab;
	char	*cmd;
	int		i;
	
	i = 0;
	path_tab = ft_split(pipex->data.env_path, ':');
	cmd = ft_join("/", cmd_arg);
	while(path_tab)
	{
		tmp = ft_strjoin(path_tab[i], cmd);
		if(access(tmp, F_OK) == 0)
		{
			pipex->data.cmd_path = tmp;
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
	
void	child(t_pipex * pipex)
{
	
	if(pipex->data.pipe_nbr == pipex->data.initial_pipe_nbr)
	{
		//c'est le premier pipe donc fermer stdout, ouvrir stdin	
	}
	if(pipex->data.pipe_nbr == 0)
	{
		//c'est le dernier pipe donc fermer stdin ouvrir stdout
	}
		dup2(pipex->files.infile_fd, STDIN_FILENO);
		dup2(pipex->data.pipe_fd[1], STDOUT_FILENO);
		execution(pipex);
}

void	execution(t_pipex *pipex)
{
	if(execve(pipex->data.cmd_path, &pipex->argv[pipex->data.arg_pos], pipex->envp) == -1);
	{
		close(pipex->data.pipe_fd[1]);
		close(pipex->data.pipe_fd[0]);
		error("execve error");
	}
}

void	parent(t_pipex *pipex, pid_t pid)
{
			waitpid(pid, NULL, 0);
}