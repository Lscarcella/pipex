/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:21 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/24 14:40:53 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	error(char *error_msg, t_pipex *pipex)
{
	red_error();
	printf(" %s", error_msg);
	free_for_all (pipex);
	exit (EXIT_FAILURE);
}

void	red_error(void)
{
	printf(COLOR_RED "Error " COLOR_WHITE);
}

void	error_while_building(t_pipex *pipex)
{
	close(pipex->files.infile_fd);
	close(pipex->files.outfile_fd);
	printf(COLOR_RED "Error " COLOR_WHITE": Unvalid command\n" );
	free_for_all(pipex);
	exit(EXIT_FAILURE);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_for_all(t_pipex *pipex)
{
	if (pipex->data.cmd_path)
	{
		free(pipex->data.cmd_path);
		pipex->data.cmd_path = NULL;
	}
	if (pipex->data.cmd_tab)
	{
		free_tab(pipex->data.cmd_tab);
		pipex->data.cmd_tab = NULL;
	}
}