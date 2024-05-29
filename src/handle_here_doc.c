/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:57:38 by lscarcel          #+#    #+#             */
/*   Updated: 2024/05/28 20:50:15 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	handle_here_doc(t_data *data)
{
	char	*buffer;

	data->tmp_file = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->tmp_file < 0)
		error("error while creating tmp_file for here_doc");
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		buffer = get_next_line(0);
		if (!buffer)
			exit (EXIT_FAILURE);
		if (ft_strcmp(buffer, data->argv[2]) == 0)
			break ;
		write(data->tmp_file, buffer, strlen(buffer));
		write(data->tmp_file, "\n", 1);
		free (buffer);
	}
	free (buffer);
	close (data->tmp_file);
	data->infile_fd = open("tmp_file", O_RDONLY);
	if (data->infile_fd < 0)
	{
		unlink("tmp_file");
		error("error while opening tmp_file");
	}
}
