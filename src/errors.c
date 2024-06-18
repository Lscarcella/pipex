/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/06/18 09:16:31 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error(char *error_msg)
{
	perror (error_msg);
	exit (EXIT_FAILURE);
}

void	close_fd(t_pipex *pipex)
{
	close(pipex->files.infile_fd);
	close(pipex->files.outfile_fd);
}
