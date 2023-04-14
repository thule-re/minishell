/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:41:17 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/14 11:15:03 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>

// Global environment variable
extern char	**environ;

typedef struct s_pipehelper {
	char	**envp;
	char	**paths;
	char	**input1;
	int		fd_index;
	int		fd_outdex;
	int		fd_in;
	int		fd_out;
	int		num_pipes;
	int		i;
	int		pipe_status;
	char	*cmd;
	int		*pipefd;
	char	*heredoc;
	int		hd_pipe[2];
}	t_pipehelper;

//functions for splitting and input parsing
char	**ft_shell_split(char *s, char c);
int		apo_count(char *str, char apo);
int		is_apo(char c);
char	next_one(char *s);
void	free_strings(char **result, int index);
void	free_arr(char **arr);
void	print_array(char **arr);
int		mod_ft_strlen(char *str, char c);
char	*get_input(int unclosed, t_pipehelper *p, char *tmp, char *tmp2);
int		is_unclosed(char *input);
char	**reformat_inputs(char **arr);
void	shift_array(char **arr, int i);

char	*delimit_this(char *s, t_pipehelper *p);
char	*expand_variables(char *s);
char	*append_var(char *s, int i, char *ret);
void	string_shift(char *s);

//Functions for pipes
int		check_input(int argc, char **argv);
int		init_params(t_pipehelper *params);
void	run_child_1(t_pipehelper *p, int in, int out);
char	*append_slash(char *path, char *str, char *c);
char	**get_path(char **envp);
char	*get_command(char **paths, char *cmd_str);
void	close_pipes(int *pipe, int size);
int		check_access(char **input);
int		ft_min(int x, int y);

//error handlers from Pipex
void	error_handler(char *s, t_pipehelper *params);
void	file_error(char *s, int fd, int error_type, t_pipehelper *params);
void	free_arr(char **arr);
void	free_arrs(t_pipehelper *params);
void	cmd_error(char *str, t_pipehelper *params);

//make input
void	make_input(t_pipehelper *p, char **parsed_input, int index);
int		are_there_pipes(char **parsed_input);

void	run_commands(t_pipehelper *p, char **parsed_input, int index);

// environment functions
char	*ft_getenv(char *str, char **envp);

#endif

// TO DO: 

// - give correct priority to either heredoc or infile input!
