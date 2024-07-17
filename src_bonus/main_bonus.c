/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:39:09 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/17 13:56:32 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc > 4)
	{
		init_struct(argc, argv, envp, &pipex);
		if (pipex.data.has_heredoc == TRUE)
		handle_here_doc(&pipex);
		set_files(&pipex);
		process(&pipex);
	}
	else
	{
		printf("Error\nWrong argument number\n");
		return (0);
	}
}
