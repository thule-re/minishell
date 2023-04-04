/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:23:21 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/04 17:36:38 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	basic_command(t_pipehelper *p, char **parsed_input)
{	
	int		pid;

	p->input1 = parsed_input;
	p->fd_in = open("infile.txt", O_RDONLY);
	p->paths = ft_split(getenv("PATH"), ':');
	p->cmd = get_command(p->paths, parsed_input[0]);
	pid = fork();
	if (pid == 0)
		run_child_1(p);
	waitpid(-1, NULL, 0);
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
			// free_arr(parsed_input);
			free(input);
			input = NULL;
		}
	}
	free(input);
	return (0);
	argc++;
	argv++;
	argc--;
	argv--;
}
