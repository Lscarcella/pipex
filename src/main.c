/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:39:09 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/23 13:58:46 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc == 5)
	{
		init_struct(argc, argv, envp, &pipex);
		set_files(&pipex);
		process(&pipex);
		free_for_all(&pipex);
	}
	else
	{
		printf("Error\nWrong argument number\n");
		return (0);
	}
}
