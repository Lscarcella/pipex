/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/16 14:48:20 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	process(t_pipex *pipex)
{
	first_cmd(pipex);
	pipex->data.cmd_nbr--;
	while(pipex->data.cmd_nbr > 1)
		middle_cmd(pipex);
	last_cmd(pipex);
}

void	first_cmd(t_pipex *pipex)
{
	pid_t pid;
	// char buffer[1000];
	int pipe_fd[2];
	
	if (pipe(pipe_fd) == -1)
	{
		error("pipe");
		exit(EXIT_FAILURE);
	}
	get_cmd(pipex, pipex->argv[pipex->data.arg_pos]);
	pid = fork();
	if (pid == -1)
		error("fork error");
	if (pid == 0)
	{
		// read(0, buffer, 1000);
		close(pipe_fd[0]);
		dup2(pipex->files.infile_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipex->files.infile_fd);
		close(pipe_fd[1]);
		execution(pipex);
	}
	waitpid(pid, NULL, 0);
	close(pipex->files.infile_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	pipex->data.arg_pos++;	
}

void	middle_cmd(t_pipex *pipex)
{
	int pipe_fd[2];
	pid_t pid;

	if(pipe(pipe_fd) == -1)
		error("pipe");
	get_cmd(pipex, pipex->argv[pipex->data.arg_pos]);
	pid = fork();
	if (pid == -1)
		error("fork error");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		execution(pipex);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	waitpid(pid, NULL, 0);
	pipex->data.cmd_nbr--;
	pipex->data.arg_pos++;
}

void	last_cmd(t_pipex *pipex)
{
	int pipe_fd[2];
	pid_t pid;

	if(pipe(pipe_fd) == -1)
		error("pipe");
	get_cmd(pipex, pipex->argv[pipex->data.arg_pos]);
	pid = fork();
	if(pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipex->files.outfile_fd, STDOUT_FILENO);
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

// char *get_cmd(t_pipex *pipex, char *cmd_arg)
// {
// 	char	*tmp_str;
// 	char	**tmp_tab;
// 	char	**path_tab;
// 	char	*cmd;
// 	int		i;
	
// 	i = 0;
// 	tmp_tab = ft_split(cmd_arg, ' ');
// 	path_tab = ft_split(pipex->data.env_path, ':');
// 	cmd = ft_join("/", tmp_tab[0]);
// 	while(path_tab[i])
// 	{
// 		tmp_str = ft_strjoin(path_tab[i], cmd);
// 		if(access(tmp_str, X_OK) == 0)
// 		{
// 			pipex->data.cmd_path = tmp_str;
// 			free(tmp_str);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	error("command not found, please enter a valid command");
// 	free(tmp_str);
// 	exit(EXIT_FAILURE);
// }

void	execution(t_pipex *pipex)
{
	char **cmd_tab;
	int i;
	i = 0;
	cmd_tab = ft_split(pipex->argv[pipex->data.arg_pos], ' ');
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
