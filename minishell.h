/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:41:17 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/04 17:17:49 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/include/libft.h"
# include <string.h>
# include <stdio.h>
# include <editline/readline.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipehelper {
	char	**envp;
	char	**paths;
	char	**input1;
	char	**input2;
	int		fd_in;
	int		fd_out;
	int		pid1;
	int		pipefd[2];
	char	*cmd;
	char	*cmd2;
	int		argc;
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
char	*get_input(int unclosed);
int		is_unclosed(char *input);

//Functions for pipes
int		check_input(int argc, char **argv);
int		init_params(t_pipehelper *params, char **envp, char **argv);
void	run_child_1(t_pipehelper *p);
void	run_child_2(t_pipehelper *p);
char	*append_slash(char *path, char *str, char *c);
char	*ft_wordsearch(char *str, char *to_find);
char	**get_path(char **envp);
char	*get_command(char **paths, char *cmd_str);

//error handlers from Pipex
void	error_handler(char *s, t_pipehelper *params);
void	file_error(char *s, int fd, int error_type, t_pipehelper *params);
void	free_arr(char **arr);
void	free_arrs(t_pipehelper *params);
void	cmd_error(char *str, t_pipehelper *params);

#endif
