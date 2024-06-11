/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:57:38 by lscarcel          #+#    #+#             */
/*   Updated: 2024/06/05 08:49:55 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	create_here_doc_file(t_pipex *pipex)
{
	pipex->files.tmp_file = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->files.tmp_file < 0)
	{
		error("error while creating tmp_file for here_doc");
		exit(EXIT_FAILURE);
	}
}

void	handle_here_doc(t_pipex *pipex)
{
	char	*buffer;
	int		bytes_read;

	create_here_doc_file(pipex);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		exit(EXIT_FAILURE);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			error("read error");
			exit(EXIT_FAILURE);
		}
		buffer[bytes_read] = '\0';
		if (ft_strncmp(buffer, pipex->argv[2], pipex->data.argv_len) == 0
			&& buffer[pipex->data.argv_len] == '\n')
			break ;
		write(pipex->files.tmp_file, buffer, ft_strlen(buffer));
	}
	free(buffer);
	close (pipex->files.tmp_file);
}
