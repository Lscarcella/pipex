/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:57:38 by lscarcel          #+#    #+#             */
/*   Updated: 2024/06/05 13:56:55 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_files(t_pipex *pipex)
{
	if (pipex->data.has_heredoc == FALSE)
		infile_check(pipex);
	open_files(pipex);
}

void	infile_check(t_pipex *pipex)
{
	if (access(pipex->argv[1], F_OK) != 0)
	{
		printf("no such file or directory: %s\n", pipex->argv[1]);
		exit (EXIT_FAILURE);
	}
	if (access(pipex->argv[1], R_OK) != 0)
	{
		printf("permission denied: %s\n", pipex->argv[1]);
		exit (EXIT_FAILURE);
	}
}

void	open_files(t_pipex *pipex)
{
	if (pipex->data.has_heredoc == FALSE)
	{
		pipex->files.infile_fd = open(pipex->argv[1], O_RDONLY);
		if (pipex->files.infile_fd == -1)
		{
			printf("Error when opening : %s", pipex->argv[1]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		pipex->files.infile_fd = open("tmp_file", O_RDONLY);
		if (pipex->files.infile_fd < 0)
		{
			unlink("tmp_file");
			error("error while opening tmp_file");
		}
	}
	pipex->files.outfile_fd = open(pipex->argv[pipex->argc - 1],
			O_WRONLY | O_CREAT, 0644);
	if (pipex->files.outfile_fd == -1)
	{
		printf("Error when opening : %s", pipex->argv[2]);
		exit(EXIT_FAILURE);
	}
}