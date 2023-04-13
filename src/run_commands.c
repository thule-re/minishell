/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:33:35 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/13 13:45:42 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	reset_inputs(t_pipehelper *p)
{
	if (p->input1)
		free_arr(p->input1);
	if (p->cmd)
		free(p->cmd);
	p->input1 = NULL;
	p->cmd = NULL;
	if (p->fd_in)
		free(p->fd_in);
	p->fd_in = NULL;
	if (p->fd_out)
		free(p->fd_out);
	p->fd_out = NULL;
}

static int	init_variables(t_pipehelper *p, char **s)
{
	int	counter;

	p->num_pipes = are_there_pipes(s);
	p->paths = ft_split(getenv("PATH"), ':');
	p->pipefd = malloc(2 * sizeof(int) * p->num_pipes);
	counter = p->num_pipes;
	while (counter--)
		pipe(&(p->pipefd[counter * 2]));
	p->i = 0;
	return (p->num_pipes);
}

int	check_access(char **input)
{
	while (*input)
	{
		if (access(*input, R_OK) == 0)
			return (1);
		input++;
	}
	return (0);
}

static void	end_running(t_pipehelper *p)
{
	if (p->fd_in)
		close(p->fd_in[0]);
	if (p->fd_out)
		close(p->fd_out[0]);
	close_pipes(p->pipefd, p->num_pipes * 2);
	free (p->pipefd);
	p->pipefd = NULL;
}

void	run_commands(t_pipehelper *p, char **parsed_input, int index)
{	
	int		pid;
	int		counter;

	counter = init_variables(p, parsed_input);
	while (counter >= 0)
	{
		make_input(p, parsed_input, index);
		if (!*parsed_input)
			break ;
		p->cmd = get_command(p->paths, p->input1[0]);
		pid = fork();
		if (pid == 0)
			run_child_1(p, p->num_in, p->num_out);
		waitpid(-1, NULL, WNOHANG);
		reset_inputs(p);
		while (parsed_input[index] && ft_strncmp("|", parsed_input[index], 2))
			index++;
		if (parsed_input[index])
			index++;
		p->i++;
		counter--;
	}
	sleep(1);
	end_running(p);
}
