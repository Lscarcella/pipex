/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/05/20 13:54:20 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	parse_args(t_data *data)
{
	if(data->has_heredoc == FALSE)
	{	
		infile_exist(data);
		infile_is_readable(data);
	}
	open_infile_outfile(data);
}
void	infile_exist(t_data *data)
{
	if(is_reachable(data, 1) != 0)
	{
		printf("no such file or directory: %s\n", data->argv[1]);	
		exit (EXIT_FAILURE);
	}
}

void	infile_is_readable(t_data *data)
{
	if(is_readable(data, 1) != 0)
	{
		printf("permission denied: %s\n", data->argv[1]);	
		exit (EXIT_FAILURE);
	}
}

void	open_infile_outfile(t_data *data)
{
	if(data->has_heredoc == FALSE)
	{
		data->infile_fd = open(data->argv[1], O_RDONLY);
		if (data->infile_fd == -1)
		{
   		 	printf("Error when opening : %s", data->argv[1]);
    		exit(EXIT_FAILURE);
		}
	}
	data->outfile_fd = open(data->argv[data->argc - 1], O_WRONLY | O_CREAT, 0644);
	if (data->outfile_fd == -1)
	{
    	printf("Error when opening : %s", data->argv[2]);
    	exit(EXIT_FAILURE);
	}
}

void	init_struct(int argc, char **argv, t_data *data)
{
	ft_memset(data, 0, sizeof(*data));
	data->argc = argc;
	data->argv = argv;
	has_heredoc(data);
}

void	has_heredoc(t_data *data)
{
	size_t	len;

	len = ft_strlen(data->argv[1]);
	if(ft_strncmp(data->argv[1], "here_doc", len) == 0)
		data->has_heredoc = 1;
}
void	delete_nl(char *buffer, int bytes_read)
{	
		if (buffer[bytes_read - 1] == '\n')
        {
            buffer[bytes_read - 1] = '\0';
            bytes_read--;
        }
}

void	first_pipe(t_data *data, char *buffer, int bytes_read)
{
	if (pipe(data->mypipe) != 0)
	{
		write(STDERR_FILENO, "pipe failed.\n", 13);
		exit(EXIT_FAILURE) ;
	}
	if (write(data->mypipe[1], buffer, bytes_read) == -1)
        {
            write(STDERR_FILENO, "write Error.\n", 13);
            exit(EXIT_FAILURE);
        }
}