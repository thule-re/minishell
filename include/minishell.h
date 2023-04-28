/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:41:17 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/27 18:15:02 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/param.h>
# include <dirent.h>

// Global environment variable
extern int	g_es;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_pipehelper {
	t_env	**envp;
	char	**paths;
	char	**input1;
	char	*usr_input;
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
	int		exit_status;
	int		dircheck;
}	t_pipehelper;

//functions for splitting and input parsing
char	**ft_shell_split(t_pipehelper *p, char *s, char c);
int		apo_count(char *str, char apo);
int		is_apo(char c);
char	next_one(char *s);
void	free_strings(char **result, int index);
void	free_arr(char **arr);
void	print_array(char **arr);
char	*get_input(t_pipehelper *p, char *tmp, char *tmp2, int line_count);
char	**reformat_inputs(t_pipehelper *p, char **arr);
void	shift_array(char **arr, int i);

char	*delimit_this(char *s, t_pipehelper *p);
char	*expand_variables(t_pipehelper *p, char *s);
void	string_shift(char *s);
int		ft_strlenc(const char *str, int c);
int		directory_handler(t_pipehelper *p, char *input, char c);
int		builtin_exit(char **parsed_input, int ret);

//Functions for pipes
int		check_input(int argc, char **argv);
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
void	free_everything(t_pipehelper *p, char **parsed_input, char *input);

//make input
void	make_input(t_pipehelper *p, char **parsed_input, int index);
int		are_there_pipes(char **parsed_input);

void	run_commands(t_pipehelper *p, char **parsed_input, int index, int pid);

//readline functions
void	rl_replace_line(const char *text, int clear_undo);

//signals
void	sigint_handler_a(int signum);
void	init_signals(void);
void	sigint_handler_b(int signum);
void	check_signals(t_pipehelper *p);

// environment functions
char	*ft_getenv(char *str, t_env *envp);
t_env	*ft_getenvp(char *str, t_env *envp);
t_env	**init_env(char **static_env);
void	free_env(t_env **envp);
t_env	*new_env_node(char **key_val);
char	**export_env(t_env *env);

// builtins
int		run_builtin(t_pipehelper *p, int forked);
int		ft_return(t_pipehelper *p, int code, int forked);
int		echo(t_pipehelper *p, int forked);
int		cd(t_pipehelper *p, int forked);
int		pwd(t_pipehelper *p, int forked);
int		export(t_pipehelper *p, int forked);
int		unset(t_pipehelper *p, int forked);
int		env(t_pipehelper *p, int forked);

#endif
