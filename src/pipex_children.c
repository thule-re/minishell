/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:46:31 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/04 14:03:00 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_child_1(t_pipehelper *p)
{
	// dup2(p->fd_in, STDIN_FILENO);
	// dup2(p->pipefd[1], STDOUT_FILENO);
	// close(p->pipefd[0]);
	// close(p->pipefd[1]);
	if (access(p->cmd, X_OK) == -1)
		cmd_error(p->cmd, p);
	if (execve(p->cmd, p->input1, p->envp) < 0)
		error_handler("execve", p);
}

void	run_child_2(t_pipehelper *p)
{
	dup2(p->pipefd[0], STDIN_FILENO);
	dup2(p->fd_out, STDOUT_FILENO);
	close(p->pipefd[1]);
	close(p->pipefd[0]);
	if (access(p->cmd2, X_OK) == -1)
		cmd_error(p->cmd2, p);
	if (execve(p->cmd2, p->input2, p->envp) < 0)
		error_handler("execve", p);
}
