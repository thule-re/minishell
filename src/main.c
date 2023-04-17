/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:23:21 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/17 15:50:28 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_es;

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
	input = get_input(1, p, NULL, NULL);
	p->usr_input = input;
	if (!input)
		return (0);
	if (!*input)
		return (1);
	p->exit_status = g_es;
	parsed_input = ft_shell_split(p, input, 32);
	if (!ft_strncmp(parsed_input[0], "exit", 5))
	{
		ft_putstr_fd("exit\n", 2);
		return (0);
	}
	add_history(input);
	signal(SIGINT, sigint_handler_b);
	run_commands(p, parsed_input, 0, 0);
	g_es = p->exit_status;
	free_everything(p, parsed_input, input);
	return (1);
}

int	main(void)
{
	t_pipehelper	p;

	init_params(&p);
	while (1)
	{
		init_signals();
		if (!minishell(&p, NULL, NULL))
			break ;
	}
	free_everything(&p, NULL, p.usr_input);
	return (0);
}
