/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:46:31 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/11 16:23:47 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipes(int *pipe, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(pipe[i]);
		i++;
	}
}

void run_helper(t_pipehelper *p, int in, int out)
{
	if (in)
		dup2(p->fd_in[p->fd_index], STDIN_FILENO);
	if (out)
		dup2(p->fd_out[p->fd_outdex], STDOUT_FILENO);
	if (p->pipe_status == 1)
	{
		if (!out)
			dup2(p->pipefd[1], STDOUT_FILENO);
		close_pipes(p->pipefd, 2);
	}
	if (p->pipe_status == 2)
	{
		if (!in)	
			dup2(p->pipefd[(p->i - 1) * 2], STDIN_FILENO);
		if (!out)
			dup2(p->pipefd[(p->i * 2) + 1], STDOUT_FILENO);
		close_pipes(p->pipefd, (p->i + 1) * 2);
	}
	if (p->pipe_status == 3)
	{
		if (!in)
			dup2(p->pipefd[p->i * 2 - 2], STDIN_FILENO);
		close_pipes(p->pipefd, p->i * 2);
	}
	if (access(p->cmd, X_OK) == -1)
		cmd_error(p->cmd, p);
	if (execve(p->cmd, p->input1, environ) < 0)
		error_handler("execve", p);
}

void	run_child_1(t_pipehelper *p, int in, int out)
{
	int	pid;

	if (out)
	{
		while (p->fd_outdex < p->num_out)
		{
			pid = fork();
			if (pid == 0)
				run_helper(p, in, p->num_out);
			p->fd_outdex++;
			waitpid(pid, NULL, WNOHANG);
		}
		p->fd_outdex = 0;		
		exit(0);
	}
	else
		run_helper(p, in, out);
}
