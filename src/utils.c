/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/05/13 13:53:30 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	parse_args(char **argv, t_data *data)
{
	infile_exist(argv);
	infile_is_readable(argv);
	open_infile_outfile(argv, data);
}
void	infile_exist(char **argv)
{
	if(is_reachable(argv, 1) != 0)
	{
		printf("no such file or directory: %s\n", argv[1]);	
		exit (EXIT_FAILURE);
	}
}

void	infile_is_readable(char **argv)
{
	if(is_readable(argv, 1) != 0)
	{
		printf("permission denied: %s\n", argv[1]);	
		exit (EXIT_FAILURE);
	}
}

void	open_infile_outfile(char **argv, t_data *data)
{	
	data->file1_fd = open(argv[1], O_RDONLY);
	if (data->file1_fd == -1)
	{
    	printf("Error when opening : %s", argv[1]);
    	exit(EXIT_FAILURE);
	}
	data->file2_fd = open(argv[4], O_WRONLY | O_CREAT, 0644);
	if (data->file2_fd == -1)
	{
    	printf("Error when opening : %s", argv[2]);
    	exit(EXIT_FAILURE);
	}
}

void	init_struct(t_data *data)
{
	ft_memset(&data, 0, sizeof(data));
}
