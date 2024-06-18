/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/06/14 11:59:55 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex(t_pipex *pipex)
{
	int i;
	
	first_cmd(pipex);
	pipex->data.cmd_nbr--;
	while(pipex->data.cmd_nbr > 1)
		middle_cmd(pipex);
	last_cmd(pipex);
}

void	first_cmd(t_pipex *pipex)
{
	pid_t pid;
	int pipe_fd[2];
	get_cmd(pipex, pipex->argv[pipex->data.arg_pos]);
	
	if (pipe(pipe_fd) == -1)
	{
		error("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		error("fork error");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipex->files.infile_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipex->files.infile_fd);
		close(pipe_fd[1]);
		execution(pipex);
	}
	waitpid(pid, NULL, 0);
	close(pipex->files.infile);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	pipex->data.arg_pos++;	
}

void	middle_cmd(t_pipex *pipex)
{
	int pipe_fd[2];
	pid_t pid;
	
	get_cmd(pipex, pipex->argv[pipex->data.arg_pos]);

	if(pipe(pipe_fd) == -1)
		error(pipe);
	pid = fork();
	if (pid == -1)
		error("fork error");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execution(pipex);
	}
	waitpid(pid, NULL, 0);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	pipex->data.cmd_nbr--;
	pipex->data.arg_pos++;
}

void	last_cmd(t_pipex *pipex)
{
	int pipe_fd[2];
	pid_t pid;

	if(pipe(pipe_fd) == -1)
		error(pipe);
	pid = fork;
	if(pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execution(pipex);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}
// void	pipe(t_pipex *pipex)
// {
// 	pid_t pid;
// 	int i;
// 	int 	pipe_fd[2];
	
// 	get_cmd(pipex, pipex->argv[pipex->data.arg_pos]);
// 	while(pipex->data.cmd_nbr > 1)
// 	{
// 	pipe(pipe_fd);
// 	pid = fork();
// 	if (pid == -1)
// 		error("error : fork returned -1");
// 	if (pid == 0)
// 		child(pipex);
// 	else
// 		parent(pipex, pid);
// 	pipex->data.cmd_nbr--;
// 	pipex->data.arg_pos++;
// 	}
// }

// char *get_cmd(t_pipex *pipex, char *cmd_arg)
// {
// 	char	*tmp;
// 	char	**path_tab;
// 	char	*cmd;
// 	int		i;
	
// 	i = 0;
// 	path_tab = ft_split(pipex->data.env_path, ':');
// 	cmd = ft_join("/", cmd_arg);
// 	while(path_tab)
// 	{
// 		tmp = ft_strjoin(path_tab[i], cmd);
// 		if(access(tmp, F_OK) == 0)
// 		{
// 			pipex->data.cmd_path = tmp;
// 			free(tmp);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	error("command not found");
// 	free(tmp);
// 	exit(EXIT_FAILURE);
// 	//fermer tout les fichiers
// }
	
// void	child(t_pipex * pipex, int 	pipe_fd[2])
// {
	
// 	if(pipex->data.pipe_nbr == pipex->data.initial_pipe_nbr)
// 	{
// 		//c'est le premier pipe donc fermer stdout, ouvrir stdin	
// 	}
// 	if(pipex->data.pipe_nbr == 0)
// 	{
// 		//c'est le dernier pipe donc fermer stdin ouvrir stdout
// 	}
// 		dup2(pipex->files.infile_fd, STDIN_FILENO);
// 		dup2(pipe_fd[1], STDOUT_FILENO);
// 		execution(pipex);
// }

void	execution(t_pipex *pipex)
{
	if(execve(pipex->data.cmd_path, &pipex->argv[pipex->data.arg_pos], pipex->envp) == -1);
	{
		// close(pipex->data.pipe_fd[1]);
		// close(pipex->data.pipe_fd[0]);
		error("execve error");
	}
}

// void	parent(t_pipex *pipex, pid_t pid)
// {
// 			waitpid(pid, NULL, 0);
// }