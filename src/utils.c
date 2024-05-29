/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/05/29 15:45:08 by lscarcel         ###   ########.fr       */
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

void	init_struct(int argc, char **argv, char **envp, t_data *data)
{
	ft_memset(data, 0, sizeof(*data));
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	has_heredoc(data);
	data->cmd_nbr = (argc - 3) - data->has_heredoc;
	data->pipe_nbr = 2 * (data->cmd_nbr - 1);
	data->argv_len = ft_strlen(data->argv[2]);
}

void	has_heredoc(t_data *data)
{
	size_t	len;

	len = ft_strlen(data->argv[1]);
	if (ft_strncmp(data->argv[1], "here_doc", len) == 0)
		data->has_heredoc = 1;
}

void	error(const char *error_msg)
{
	perror (error_msg);
	exit (EXIT_FAILURE);
}
