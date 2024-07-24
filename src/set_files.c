/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:57:38 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/24 14:35:29 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_files(t_pipex *pipex)
{
	infile_check(pipex);
	open_files(pipex);
}

void	infile_check(t_pipex *pipex)
{
	if (access(pipex->argv[1], F_OK) != 0)
	{
		red_error();
		printf(": no such file or directory : %s\n", pipex->argv[1]);
		exit (EXIT_FAILURE);
	}
	if (access(pipex->argv[1], R_OK) != 0)
	{
		red_error();
		printf(": permission denied : %s\n", pipex->argv[1]);
		exit (EXIT_FAILURE);
	}
}

void	open_files(t_pipex *pipex)
{
	pipex->files.infile_fd = open(pipex->argv[1], O_RDONLY);
	if (pipex->files.infile_fd == -1)
	{
		red_error();
		printf(" Cant open : %s", pipex->argv[1]);
		exit(EXIT_FAILURE);
	}
	pipex->files.outfile_fd = open(pipex->argv[pipex->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->files.outfile_fd == -1)
	{
		red_error();
		printf(" Cant open : %s", pipex->argv[2]);
		exit(EXIT_FAILURE);
	}
}
