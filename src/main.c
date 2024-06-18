/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:39:09 by lscarcel          #+#    #+#             */
/*   Updated: 2024/06/18 09:21:31 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
		printf("wrong arguments number\n");
		return (0);
	}
}
