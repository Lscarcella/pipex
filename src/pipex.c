/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/24 14:33:47 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	process(t_pipex *pipex)
{
	first_cmd(pipex);
	free_for_all(pipex);
	last_cmd(pipex);
}

void	first_cmd(t_pipex *pipex)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		error("pipe", pipex);
	get_cmd(pipex, pipex->argv[2]);
	pid = fork();
	if (pid == -1)
		error("fork error", pipex);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipex->files.infile_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipex->files.infile_fd);
		close(pipex->files.outfile_fd);
		close(pipe_fd[1]);
		execution(pipex);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipex->files.infile_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	waitpid(pid, NULL, 0);
}

void	last_cmd(t_pipex *pipex)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		error("pipe", pipex);
	get_cmd(pipex, pipex->argv[3]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipex->files.outfile_fd, STDOUT_FILENO);
		close(pipex->files.outfile_fd);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		execution(pipex);
	}
	close(pipex->files.outfile_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	waitpid(pid, NULL, 0);
}

void	execution(t_pipex *pipex)
{
	if (execve(pipex->data.cmd_path, pipex->data.cmd_tab, pipex->envp) == -1)
		error("execve error", pipex);
}
