/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:35:47 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/24 16:00:19 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SO_LONG_H
# include <stdlib.h>
# include "../libs/libft/libft.h"
#include <sys/wait.h>

# define SO_LONG_H
# define WIDTH		256
# define HEIGHT		256
# define TRUE		1
# define FALSE		0
# define SUCCESS	0
# define FAIL		1

typedef struct s_files
{
	int		infile_fd;
	int		outfile_fd;
	int		tmp_file;
	char	*infile;
}	t_files;

typedef struct s_data
{
	int		has_heredoc;
	int		arg_pos;
	int		cmd_nbr;
	int		pipe_nbr;
	int		initial_pipe_nbr;
	char	*env_path;
	char	*cmd_path;
	char	**cmd_tab;
	size_t	argv_len;
}	t_data;

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	t_files	files;
	t_data	data;
}	t_pipex;

// Handle_files
void	set_files(t_pipex *pipex);
void	infile_check(t_pipex *pipex);
void	open_files(t_pipex *pipex);

// Handle_here_doc
void	create_here_doc_file(t_pipex *pipex);
void	handle_here_doc(t_pipex *pipex);

//pipex
void	process(t_pipex *pipex);
void	get_cmd(t_pipex *pipex, char *cmd_arg);
void	execution(t_pipex *pipex);
void	first_cmd(t_pipex *pipex);
void	middle_cmd(t_pipex *pipex);
void	last_cmd(t_pipex *pipex);
void	error(char *error_msg, t_pipex *pipex);
void	red_error(void);
void	error_while_building(t_pipex *pipex);
void	free_tab(char **tab);
void	free_for_all(t_pipex *pipex);


//utils
void	init_struct(int argc, char **argv, char **envp, t_pipex *pipex);
void	has_heredoc(t_pipex *pipex);
char	*get_path(char **envp);
void	build_cmd(t_pipex *pipex);
void	free_tab(char **tab);
// char	*ft_join(char *s1, char const *s2);

//error
// void	error(char *error_msg);
void	close_fd(t_pipex *pipex);


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
