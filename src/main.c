/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:23:21 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/16 11:27:37 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_everything(t_pipehelper *p, char **parsed_input, char *input)
{
	free_arrs(p);
	if (p->heredoc)
		free(p->heredoc);
	if (parsed_input)
		free_arr(parsed_input);
	if (input)
		free(input);
	p->heredoc = NULL;
	parsed_input = NULL;
	input = NULL;
}

static int	minishell(t_pipehelper *p, char *input, char **parsed_input)
{
	static int	es = 0;

	input = get_input(1, p, NULL, NULL);
	p->usr_input = input;
	if (!*input)
		return (1);
	p->exit_status = es;
	if (!ft_strncmp(input, "exit", 5))
		return (0);
	parsed_input = ft_shell_split(p, input, 32);
	if (!ft_strncmp(parsed_input[0], "exit", 5))
		return (0);
	add_history(input);
	run_commands(p, parsed_input, 0, 0);
	es = p->exit_status;
	free_everything(p, parsed_input, input);
	return (1);
}

int	main(void)
{
	t_pipehelper	p;

	init_params(&p);
	while (1)
	{
		if (!minishell(&p, NULL, NULL))
			break ;
	}
	free_everything(&p, NULL, p.usr_input);
	return (0);
}
