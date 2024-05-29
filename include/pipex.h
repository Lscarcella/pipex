/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozkuro <lozkuro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:37:51 by lscarcel          #+#    #+#             */
/*   Updated: 2024/05/28 20:49:53 by lozkuro          ###   ########.fr       */
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
	int		tmp_file;
	int		outfile_fd;
	int		has_heredoc;
	int 	argc;
	char	**argv;
	char	**envp;
	char	*infile;
	int 	pipe_fd[2];
	int		cmd_nbr;
	int		pipe_nbr;
}	t_data;


void	init_struct(int argc, char **argv, char **envp, t_data *data);
int		is_reachable(t_data *data, int i);
int 	is_readable(t_data *data, int i);
int 	is_executable(t_data *data, int i);
void	infile_check(t_data *data);
void	open_infile_outfile(t_data *data);
void	parse_args(t_data *data);
void	has_heredoc(t_data *data);
void	handle_here_doc(t_data *data);
void	error(char *err);

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
