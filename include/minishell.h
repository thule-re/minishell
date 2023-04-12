/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:41:17 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/12 12:30:08 by awilliam         ###   ########.fr       */
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
	int		num_in;
	int		fd_index;
	int		fd_outdex;
	int		*fd_in;
	int		num_out;
	int		*fd_out;
	int		num_pipes;
	int		i;
	int		pipe_status;
	char	*cmd;
	char	*cmd2;
	int		*pipefd;
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
char	**reformat_inputs(char **arr);
void	shift_array(char **arr, int i);

//Functions for pipes
int		check_input(int argc, char **argv);
int		init_params(t_pipehelper *params);
void	run_child_1(t_pipehelper *p, int in, int out);
char	*append_slash(char *path, char *str, char *c);
char	*ft_wordsearch(char *str, char *to_find);
char	**get_path(char **envp);
char	*get_command(char **paths, char *cmd_str);
void	close_pipes(int *pipe, int size);

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

#endif

// Commands to test against shell:

// Working:

// Not working:

// cat -e infile.txt | grep str >out
// cat -e infile.txt >out1 | grep str >out
// cat -e infile.txt >out1 >out2 | grep str >out3 >out4
// cat -e <infile.txt <infile.txt | grep str <infile.txt >out1
// cat -e < infile.txt < infile.txt <infile.txt | grep str <infile.txt >outfile
	// (Why is the output getting flipped around???)

// HOW DOES HEREDOC WORK?

// - takes input like in and out with a "<<"
// - Input comes in at the end of the command no matter what
// - Works differently with cat command...
// - When delimiter is in quotes, variables don't expand, otherwise they do.


// METHOD IDEA - Store all heredoc info in a string, pass this as
	// last argument into the commands
	// How does heredoc handle quotes? Probably should place it after quote logic

// TO DO: 

// - Quote handling input: Make newlines work as shell, i.e. 
// 	echo "hello
// 	world"
// - 
