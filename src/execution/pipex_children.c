/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:46:31 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/01 12:28:01 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	set_pipes(t_minishell *p, int in, int out)
{
	if (p->pipe_status == 1)
	{
		if (!out)
			dup2(p->pipefd[1], STDOUT_FILENO);
		close_pipes(p->pipefd, 2);
	}
	if (p->pipe_status == 2)
	{
		if (!in && !p->heredoc)
			dup2(p->pipefd[(p->i - 1) * 2], STDIN_FILENO);
		if (!out)
			dup2(p->pipefd[(p->i * 2) + 1], STDOUT_FILENO);
		close_pipes(p->pipefd, (p->i + 1) * 2);
	}
	if (p->pipe_status == 3)
	{
		if (!in && !p->heredoc)
			dup2(p->pipefd[p->i * 2 - 2], STDIN_FILENO);
		close_pipes(p->pipefd, p->i * 2);
	}
}

void	run_helper(t_minishell *p, int in, int out)
{
	set_pipes(p, in, out);
	if (run_builtin(p, 1))
		return ;
	if (access(p->cmd, X_OK) == -1 || p->dircheck)
		cmd_error(p->input1[0], p);
	if (execve(p->cmd, p->input1, export_env(*p->envp)) < 0)
		error_handler("execve", p);
}

void	run_child_1(t_minishell *p, int in, int out)
{
	if (p->heredoc && !(check_access(p->input1)) && !p->fd_in)
	{
		dup2(p->hd_pipe[0], STDIN_FILENO);
		close_pipes(&p->hd_pipe[0], 2);
	}
	if (in)
		dup2(p->fd_in, STDIN_FILENO);
	if (out)
		dup2(p->fd_out, STDOUT_FILENO);
	run_helper(p, in, out);
}
