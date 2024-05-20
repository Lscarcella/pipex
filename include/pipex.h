/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:37:51 by lscarcel          #+#    #+#             */
/*   Updated: 2024/05/20 13:55:29 by lozkuro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# include <stdlib.h>
# include "../libs/libft/libft.h"

# define SO_LONG_H
# define WIDTH		256
# define HEIGHT		256
# define TRUE		1
# define FALSE		0
# define SUCCESS	0
# define FAIL		1

typedef	struct s_data
{
	int 	infile_fd;
	int		outfile_fd;
	int		has_heredoc;
	int 	argc;
	char	**argv;
	char	*infile;
	pid_t	pid_father;
	pid_t	pid_son;
	int 	mypipe[2];
}	t_data;


void	init_struct(int argc, char **argv, t_data *data);
int		is_reachable(t_data *data, int i);
int 	is_readable(t_data *data, int i);
int 	is_executable(t_data *data, int i);
void	infile_exist(t_data *data);
void	infile_is_readable(t_data *data);
void	open_infile_outfile(t_data *data);
void	parse_args(t_data *data);
void	has_heredoc(t_data *data);
void	handle_here_doc(t_data *data);
void	without_here_doc(t_data *data);
void	with_here_doc(t_data *data);
void	first_pipe(t_data *data, char *buffer, int bytes_read);
void	delete_nl(char *buffer, int bytes_read);


// Colors
# define COLOR_BLACK "\033[0;30m" // Black
# define COLOR_RED "\033[0;91m" // Red
# define COLOR_GREEN "\033[0;32m" // Green
# define COLOR_YELLOW "\033[0;33m" // Yellow
# define COLOR_BLUE "\033[0;34m" // Blue
# define COLOR_PURPLE "\033[0;35m" // Purple
# define COLOR_CYAN "\033[0;36m" // Cyan
# define COLOR_WHITE "\033[0m" // White
# define TEXT_BOLD "\033[1m" // Bold text
# define TEXT_RESET "\033[0m" // Reset text attributes

#endif 
