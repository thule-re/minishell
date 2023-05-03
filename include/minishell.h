/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:41:17 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/02 15:31:37 by treeps           ###   ########.fr       */
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
# include "malloc.h"

// Global environment variable
extern int	g_es;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell {
	t_env	**envp;
	char	**paths;
	char	**split_input;
	char	**input1;
	char	*usr_input;
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
}	t_minishell;

// functions for splitting and input parsing
char	**ft_shell_split(t_minishell *p, char *s, char c);
int		apo_count(char *str, char apo);
int		is_apo(char c);
char	next_one(char *s);
void	free_strings(char **result, int index);
void	free_arr(char **arr);
void	print_array(char **arr);
char	*get_input(t_minishell *p, char *tmp, char *tmp2, int status);
char	**reformat_inputs(t_minishell *p, char **arr);
void	shift_array(char **arr, int i);
int		special_no_quotes(char *s);

char	*delimit_this(char *s, t_minishell *p, char *delim);
char	*expand_variables(t_minishell *p, char *s);
void	string_shift(char *s);
int		directory_handler(t_minishell *p, char *input, char c);

// functions for pipes
void	run_child_1(t_minishell *p, int in, int out);
char	*append_slash(char *path, char *str, char *c);
char	*get_command(char **paths, char *cmd_str);
void	close_pipes(int *pipe, int size);
int		check_access(char **input);
int		ft_min(int x, int y);
void	end_running(t_minishell *p);
void	open_heredoc_pipe(t_minishell *p);

// error handlers
void	error_handler(char *s, t_minishell *params);
void	malloc_error(t_minishell *params, int free, int exit);
void	file_error(char *s, int fd, int error_type, t_minishell *params);
void	cmd_error(char *str, t_minishell *params);
void	parse_error(char *s);

// free handlers
void	free_arr(char **arr);
void	free_arrs(t_minishell *params);
void	free_everything(t_minishell *p, t_env **env);

// make input
void	make_input(t_minishell *p, char **split_input, int index);
int		are_there_pipes(char **parsed_input);
char	*remove_apos(t_minishell *p, char *s, char *ret, int len);
int		is_special_char(char *s);
int		check_syntax(char **arr);
int		init_variables(t_minishell *p, char **s);
void	run_commands(t_minishell *p, int index, int pid, int counter);

// readline functions
void	rl_replace_line(const char *text, int clear_undo);

// signals
void	sigint_handler_a(int signum);
void	init_signals(void);
void	sigint_handler_b(int signum);
void	check_signals(t_minishell *p);

// environment functions
char	*ft_getenv(char *str, t_env *envp);
t_env	*ft_getenvp(char *str, t_env *envp);
t_env	**init_env(char **static_env);
void	free_env(t_env **envp);
t_env	*new_env_node(char **key_val);
char	**export_env(t_env *env);

// builtins
int		run_builtin(t_minishell *p, int forked);
int		echo(t_minishell *p, int forked);
int		cd(t_minishell *p, int forked);
int		pwd(t_minishell *p, int forked);
int		export(t_minishell *p, int forked);
int		unset(t_minishell *p, int forked);
int		env(t_minishell *p, int forked);
int		ft_return(t_minishell *p, int code, int forked);
int		builtin_exit(char **parsed_input, int ret);

#endif
