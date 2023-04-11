/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:33:35 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/11 12:53:05 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	reset_inputs(t_pipehelper *p)
{
	free_arr(p->input1);
	free(p->cmd);
	p->input1 = NULL;
	p->cmd = NULL;
	if (p->fd_in)
		free(p->fd_in);
	p->fd_in = NULL;
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

void	run_commands(t_pipehelper *p, char **parsed_input, int index)
{	
	int		pid;
	int		counter;

	counter = init_variables(p, parsed_input);
	while (counter >= 0)
	{
		make_input(p, parsed_input, index);
		p->cmd = get_command(p->paths, p->input1[0]);
		if (index || !p->fd_in || check_access(p->input1))
		{
			pid = fork();
			if (pid == 0)
				run_child_1(p, 0, p->num_out);
			waitpid(-1, NULL, WNOHANG);
		}
		if (p->fd_in && !(check_access(p->input1)))
		{
			while (p->fd_index < p->num_in)
			{
				pid = fork();
				if (pid == 0)
					run_child_1(p, 1, p->num_out);
				waitpid(-1, NULL, WNOHANG);
				p->fd_index++;
			}
			p->fd_index = 0;
		}
		reset_inputs(p);
		while (parsed_input[index] && ft_strncmp("|", parsed_input[index], 2))
			index++;
		if (parsed_input[index])
			index++;
		p->i++;
		counter--;
	}
	sleep(1);
	if (p->fd_in)
	{
		while (p->num_in--)
			close(p->fd_in[p->num_in]);
	}
	if (p->fd_out)
	{
		while (p->num_out--)
			close(p->fd_out[p->num_out]);
	}
	close_pipes(p->pipefd, p->num_pipes * 2);
	free (p->pipefd);
	p->pipefd = NULL;
}
