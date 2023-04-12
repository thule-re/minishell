/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:23:21 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/12 12:26:27 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_everything(t_pipehelper *p, char **parsed_input, char *input)
{
	free_arrs(p);
	if (parsed_input)
		free_arr(parsed_input);
	if (input)
		free(input);
	if (p->fd_in)
		free(p->fd_in);
	if (p->fd_out)
		free(p->fd_out);
	p->fd_out = NULL;
	p->fd_in = NULL;
	parsed_input = NULL;
	input = NULL;
}

int	main(void)
{
	char			**parsed_input;
	char			*input;
	t_pipehelper	p;

	init_params(&p);
	parsed_input = NULL;
	input = NULL;
	while (1)
	{
		waitpid(-1, NULL, 0);
		input = get_input(1);
		if (*input)
		{
			add_history(input);
			if (!ft_strncmp(input, "exit", 6))
				break ;
			parsed_input = ft_shell_split(input, 32);
			run_commands(&p, parsed_input, 0);
			free_everything(&p, parsed_input, input);
		}
	}
	free_everything(&p, NULL, input);
	return (0);
}
