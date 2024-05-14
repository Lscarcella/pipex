/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:19:40 by lscarcel          #+#    #+#             */
/*   Updated: 2024/05/13 11:29:47 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int is_reachable(char **argv, int i)
{
	if(access(argv[i], F_OK) == 0)
		return(SUCCESS);
	else
		return(FAIL);
}


int is_readable(char **argv, int i)
{
	if(access(argv[i], R_OK) == 0)
		return(SUCCESS);
	else
		return(FAIL);
}

int is_executable(char **argv, int i)
{
	if(access(argv[i], X_OK) == 0)
		return(SUCCESS);
	else
		return(FAIL);
}