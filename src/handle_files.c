/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:57:38 by lscarcel          #+#    #+#             */
/*   Updated: 2024/06/04 16:55:22 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_files(t_data *data)
{
	if (data->has_heredoc == FALSE)
		infile_check(data);
	open_files(data);
}

void	infile_check(t_data *data)
{
	if (access(data->argv[1], F_OK) != 0)
	{
		printf("no such file or directory: %s\n", data->argv[1]);
		exit (EXIT_FAILURE);
	}
	if (access(data->argv[1], R_OK) != 0)
	{
		printf("permission denied: %s\n", data->argv[1]);
		exit (EXIT_FAILURE);
	}
}

void	open_files(t_data *data)
{
	if (data->has_heredoc == FALSE)
	{
		data->infile_fd = open(data->argv[1], O_RDONLY);
		if (data->infile_fd == -1)
		{
			printf("Error when opening : %s", data->argv[1]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		data->infile_fd = open("tmp_file", O_RDONLY);
		if (data->infile_fd < 0)
		{
			unlink("tmp_file");
			error("error while opening tmp_file");
		}
	}
	data->outfile_fd = open(data->argv[data->argc - 1],
			O_WRONLY | O_CREAT, 0644);
	if (data->outfile_fd == -1)
	{
		printf("Error when opening : %s", data->argv[2]);
		exit(EXIT_FAILURE);
	}
}