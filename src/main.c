/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:39:09 by lscarcel          #+#    #+#             */
/*   Updated: 2024/05/29 15:42:29 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 4)
	{
		init_struct(argc, argv, envp, &data);
		if (data.has_heredoc == TRUE)
			handle_here_doc(&data);
		set_files(&data);
	}
	else
	{
		printf("wrong arguments number\n");
		return (0);
	}
}
