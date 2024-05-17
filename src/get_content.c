/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:19:40 by lscarcel          #+#    #+#             */
/*   Updated: 2024/05/15 08:15:13 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int is_reachable(t_data *data, int i)
{
	if(access(data->argv[i], F_OK) == 0)
		return(SUCCESS);
	else
		return(FAIL);
}


int is_readable(t_data *data, int i)
{
	if(access(data->argv[i], R_OK) == 0)
		return(SUCCESS);
	else
		return(FAIL);
}

int is_executable(t_data *data, int i)
{
	if(access(data->argv[i], X_OK) == 0)
		return(SUCCESS);
	else
		return(FAIL);
}