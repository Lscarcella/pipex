/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/17 13:55:07 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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
