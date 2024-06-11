/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:39:09 by lscarcel          #+#    #+#             */
/*   Updated: 2024/06/05 08:35:27 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc > 3)
	{
		init_struct(argc, argv, envp, &pipex);
		if (pipex.data.has_heredoc == TRUE)
			handle_here_doc(&pipex);
		set_files(&pipex);
		pipe(&pipex);
	}
	else
	{
		printf("wrong arguments number\n");
		return (0);
	}
}
