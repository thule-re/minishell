/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:23:21 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/05 17:44:43 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	are_there_pipes(char **parsed_input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (parsed_input[i])
	{
		if (!ft_strncmp("|", parsed_input[i], 2))
			count++;
		i++;
	}
	return (count);
}

int	make_count(char **parsed_input, int index)
{
	int count;

	count = 0;
	while (parsed_input[index])
	{
		if (!ft_strncmp("|", parsed_input[index], 2))
			break;
		count++;
		index++;
	}
	return (count);
}

//pipe status: 1 = at beginning, 2 = middle, 3 = end, 4 = no pipes
void	make_input(t_pipehelper *p, char **parsed_input, int index)
{
	int	count;
	int	i;

	i = 0;
	count = make_count(parsed_input, index);
	p->input1 = malloc(sizeof(char *) * (count + 1));
	while (i < count)
	{	
		p->input1[i] = ft_strdup(parsed_input[index + i]);
		i++;
	}
	p->input1[i] = 0;
	if (!are_there_pipes(parsed_input))
		p->pipe_status = 4;
	else if (index == 0)
		p->pipe_status = 1;
	else if (are_there_pipes(&parsed_input[index]))
		p->pipe_status = 2;
	else
		p->pipe_status = 3;
}

void	basic_command(t_pipehelper *p, char **parsed_input)
{	
	int		pid;
	int		i;
	int		num_pipes;

	num_pipes = are_there_pipes(parsed_input);
	i = 0;
	p->paths = ft_split(getenv("PATH"), ':');
	p->pipefd = malloc(2 * sizeof(int) * num_pipes);
	while (num_pipes--)
		pipe(&(p->pipefd[num_pipes * 2]));
	p->i = 0;
	num_pipes = are_there_pipes(parsed_input);
	while (num_pipes >= 0)
	{
		make_input(p, parsed_input, i);
		p->cmd = get_command(p->paths, p->input1[0]);
		print_array(p->input1);
		pid = fork();
		if (pid == 0)
			run_child_1(p);
		waitpid(-1, NULL, WNOHANG);
		free_arr(p->input1);
		free(p->cmd);
		p->input1 = NULL;
		p->cmd = NULL;
		while (parsed_input[i] && ft_strncmp("|", parsed_input[i], 2))
			i++;
		if (parsed_input[i])
			i++;
		p->i++;
		num_pipes--;
		ft_printf("%i\n", num_pipes);
	}
	num_pipes = are_there_pipes(parsed_input);
	close_pipes(p->pipefd, num_pipes * 2);
	free (p->pipefd);
}

//NEXT STEPS:
// - Make it run with a new process and just basic commands

int	main(int argc, char **argv, char **envp)
{
	char			**parsed_input;
	char			*input;
	t_pipehelper	p;

	p.envp = envp;
	input = NULL;
	while (1)
	{
		waitpid(-1, NULL, WNOHANG);
		input = get_input(1);
		if (*input)
		{
			add_history(input);
			if (!ft_strncmp(input, "exit", 6))
				break ;
			parsed_input = ft_shell_split(input, 32);
			basic_command(&p, parsed_input);
			// print_array(parsed_input);
			// do actions based on input
			free_arrs(&p);
			free_arr(parsed_input);
			parsed_input = NULL;
			if (input)
				free(input);
			input = NULL;
		}
	}
	free_arrs(&p);
	if (parsed_input)
		free_arr(parsed_input);
	free(input);
	return (0);
	argc++;
	argv++;
	argc--;
	argv--;
}
