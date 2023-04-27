/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:23:21 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/27 17:46:18 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_es;

static int	init_params(t_pipehelper *params)
{
	params->dircheck = 0;
	params->usr_input = NULL;
	params->input1 = NULL;
	params->cmd = NULL;
	params->paths = NULL;
	params->heredoc = NULL;
	params->i = 0;
	params->fd_index = 0;
	params->fd_outdex = 0;
	params->fd_in = 0;
	params->fd_out = 0;
	params->envp = init_env(environ);
	return (1);
}

static int	minishell(t_pipehelper *p, char *input, char **parsed_input)
{
	input = get_input(1, p, NULL, NULL);
	if (!input)
		return (1);
	if (!*input)
		return (-1);
	if  (!directory_handler(p, input, 0))
		return (-1);
	p->usr_input = input;
	p->exit_status = g_es;
	parsed_input = ft_shell_split(p, input, 32);
	if (!parsed_input || !*parsed_input)
		return (-1);
	if (!ft_strncmp(parsed_input[0], "exit", 5))
		return (builtin_exit(parsed_input, -1));
	add_history(input);
	signal(SIGINT, sigint_handler_b);
	run_commands(p, parsed_input, 0, 0);
	g_es = p->exit_status;
	free_everything(p, parsed_input, input);
	return (-1);
}

int	main(void)
{
	t_pipehelper	p;
	int				es;

	es = -1;
	init_params(&p);
	while (es < 0)
	{
		init_signals();
		es = minishell(&p, NULL, NULL);
	}
	if (p.envp)
		free_env(p.envp);
	free_everything(&p, NULL, p.usr_input);
	exit(es);
}
