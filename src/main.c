/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:39:09 by lscarcel          #+#    #+#             */
/*   Updated: 2024/06/20 21:33:35 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	char *file_path = "/bin/ls";
	char *args[] = {"ls", "-l", NULL};
	char **env = envp;

	printf("%d", execve(file_path, args, env));
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
