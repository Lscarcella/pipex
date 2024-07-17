/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/17 11:28:01 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	process(t_pipex *pipex)
{
	first_cmd(pipex);
	last_cmd(pipex);
}

void	first_cmd(t_pipex *pipex)
{
	pid_t pid;
	int pipe_fd[2];
	
	if (pipe(pipe_fd) == -1)
	{
		error("pipe");
		exit(EXIT_FAILURE);
	}
	get_cmd(pipex, pipex->argv[2]);
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
		execution(pipex, 2);
	}
	waitpid(pid, NULL, 0);
	close(pipex->files.infile_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	last_cmd(t_pipex *pipex)
{
	int pipe_fd[2];
	pid_t pid;

	if(pipe(pipe_fd) == -1)
		error("pipe");
	get_cmd(pipex, pipex->argv[3]);
	pid = fork();
	if(pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipex->files.outfile_fd, STDOUT_FILENO);
		close(pipe_fd[1]);
		execution(pipex, 3);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

void	execution(t_pipex *pipex, int pos)
{
	char **cmd_tab;
	int i;
	i = 0;
	cmd_tab = ft_split(pipex->argv[pos], ' ');
	cmd_tab[0] = pipex->data.cmd_path;
	if (execve(pipex->data.cmd_path, cmd_tab, pipex->envp) == -1)
	{
		error("execve error");
		exit(EXIT_FAILURE);
	}
	while(cmd_tab[i])
	{
		free(cmd_tab[i]);
		i++;
	}
	free(pipex->data.cmd_path);
}
