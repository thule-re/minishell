/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:33:35 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/02 17:00:30 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	reset_inputs(t_minishell *p)
{
	if (p->input1)
		free_arr(p->input1);
	if (p->cmd)
		free(p->cmd);
	p->input1 = NULL;
	p->cmd = NULL;
	p->fd_in = 0;
	p->fd_out = 0;
}

int	init_variables(t_minishell *p, char **s)
{
	int		counter;
	char	*path;

	p->num_pipes = are_there_pipes(s);
	path = ft_getenv("PATH", *p->envp);
	if (path)
		p->paths = ft_split(path, ':');
	else
		p->paths = NULL;
	p->pipefd = malloc(2 * sizeof(int) * p->num_pipes);
	counter = p->num_pipes;
	while (counter--)
		pipe(&(p->pipefd[counter * 2]));
	p->i = 0;
	return (p->num_pipes);
}

void	end_running(t_minishell *p)
{
	if (p->fd_in)
		close(p->fd_in);
	if (p->fd_out)
		close(p->fd_out);
	if (p->pipefd)
	{
		close_pipes(p->pipefd, p->num_pipes * 2);
		free (p->pipefd);
	}
	p->pipefd = NULL;
}

void	close_outs(int *pipe, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i % 2)
			close(pipe[i]);
		i++;
	}
}

void	run_commands(t_minishell *p, int i, int pid, int counter)
{
	while (counter >= 0)
	{
		make_input(p, p->split_input, i);
		if (!p->input1)
			return (malloc_error(p, 1, 0));
		if (!*p->split_input || !*(p->input1))
			return (free_everything(p, p->envp));
		if (!(p->num_pipes == 0 && run_builtin(p, 0)))
		{
			pid = fork();
			if (pid == 0)
				run_child_1(p, p->fd_in, p->fd_out);
		}
		reset_inputs(p);
		while (p->split_input[i] && ft_strncmp("|", p->split_input[i], 2))
			i++;
		if (p->split_input[i])
			i++;
		p->i++;
		counter--;
		if (counter >= 0 && p->num_pipes)
			close_outs(p->pipefd, p->i * 2);
	}
	waitpid(pid, &p->exit_status, 0);
	check_signals(p);
	end_running(p);
}
