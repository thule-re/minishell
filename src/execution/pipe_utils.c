/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:23:34 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/04 12:28:53 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (p->pipe_status == 4 && p->heredoc)
		dup2(p->hd_pipe[0], STDIN_FILENO);
}
