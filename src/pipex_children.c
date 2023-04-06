/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:46:31 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/06 09:26:50 by awilliam         ###   ########.fr       */
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

// (for later when the fd-in is needed)
// dup2(p->fd_in, STDIN_FILENO);
void	run_child_1(t_pipehelper *p)
{
	if (p->pipe_status == 1)
	{
		dup2(p->pipefd[1], STDOUT_FILENO);
		close_pipes(p->pipefd, 2);
	}
	if (p->pipe_status == 2)
	{
		dup2(p->pipefd[(p->i - 1) * 2], STDIN_FILENO);
		dup2(p->pipefd[(p->i * 2) + 1], STDOUT_FILENO);
		close_pipes(p->pipefd, (p->i + 1) * 2);
	}
	if (p->pipe_status == 3)
	{
		dup2(p->pipefd[p->i * 2 - 2], STDIN_FILENO);
		close_pipes(p->pipefd, p->i * 2);
	}
	if (access(p->cmd, X_OK) == -1)
		cmd_error(p->cmd, p);
	if (execve(p->cmd, p->input1, environ) < 0)
		error_handler("execve", p);
}
