/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   with_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:57:38 by lscarcel          #+#    #+#             */
/*   Updated: 2024/05/20 13:55:57 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	with_here_doc(t_data *data)
{
	parse_args(data);
	handle_here_doc(data);
}

void	handle_here_doc(t_data *data)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			write(STDERR_FILENO, "read Error.\n", 13);
			exit(EXIT_FAILURE) ;
		}
		buffer[bytes_read] = '\0';
		delete_nl(buffer, bytes_read);
		first_pipe(data, buffer, bytes_read);
		if (bytes_read > 0 && ft_strcmp(buffer, data->argv[2]) == 0)
			break;
	}
	free(buffer);
	close(data->mypipe[0]);
    close(data->mypipe[1]);
}
