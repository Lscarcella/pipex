/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   with_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:57:38 by lscarcel          #+#    #+#             */
/*   Updated: 2024/05/17 15:45:28 by lscarcel         ###   ########.fr       */
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
	int mypipe[2];

		if (pipe(mypipe) != 0)
		{
    		write(STDERR_FILENO, "pipe failed.\n", 13);
    		exit(EXIT_FAILURE) ;
		}
	buffer = malloc(1);
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
		if (write(mypipe[1], buffer, bytes_read) == -1)
        {
            write(STDERR_FILENO, "write Error.\n", 13);
            exit(EXIT_FAILURE);
        }
		if (bytes_read > 0 && ft_strncmp(buffer, data->argv[2], bytes_read - 1) == 0)
			break;
	}
	free(buffer);
	close(mypipe[0]);
    close(mypipe[1]);
}
