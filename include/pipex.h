/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:37:51 by lscarcel          #+#    #+#             */
/*   Updated: 2024/06/05 16:18:10 by lscarcel         ###   ########.fr       */
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

typedef	struct s_pipex
{
	int 	argc;
	char	**argv;
	char	**envp;
	t_files	files;
	t_data	data;
}	t_pipex;

typedef	struct s_files
{
	int 	infile_fd;
	int		outfile_fd;
	int		tmp_file;
	char	*infile;
}	t_files;

typedef	struct s_data
{
	int		has_heredoc;
	int 	pipe_fd[2];
	int		arg_pos;
	int		cmd_nbr;
	int		pipe_nbr;
	int		initial_pipe_nbr;
	char	*env_path;
	char	*cmd_path;
	size_t	argv_len;
}	t_data;

// Handle_files
void	set_files(t_data *data);
void	infile_check(t_data *data);
void	open_files(t_data *data);

// Handle_here_doc
void	create_here_doc_file(t_data *data);
void	handle_here_doc(t_data *data);

//pipex
void	pipe(t_data *data);
char 	*get_cmd(t_data *data, char *cmd_arg);
void	child(t_data * data);
void	execution(t_data *data);
void	parent(t_data *data, pid_t pid);

//utils
void	init_struct(int argc, char **argv, char **envp, t_data *data);
void	has_heredoc(t_data *data);
char	*get_path(char **envp);
char	*ft_join(char *s1, char const *s2);

//error
void	error(const char *error_msg);
void	close(t_data *data);


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
