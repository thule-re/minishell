/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:33:35 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/06 10:00:05 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	run_commands(t_pipehelper *p, char **parsed_input, int index)
{	
	int		pid;
	int		counter;

	counter = init_variables(p, parsed_input);
	while (counter >= 0)
	{
		make_input(p, parsed_input, index);
		p->cmd = get_command(p->paths, p->input1[0]);
		pid = fork();
		if (pid == 0)
			run_child_1(p);
		waitpid(-1, NULL, WNOHANG);
		free_arr(p->input1);
		free(p->cmd);
		p->input1 = NULL;
		p->cmd = NULL;
		while (parsed_input[index] && ft_strncmp("|", parsed_input[index], 2))
			index++;
		if (parsed_input[index])
			index++;
		p->i++;
		counter--;
	}
	close_pipes(p->pipefd, p->num_pipes * 2);
	free (p->pipefd);
}
