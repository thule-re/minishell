/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:23:21 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/01 12:28:01 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_es;

static int	init_params(t_minishell *params, char **envp)
{
	params->split_input = NULL;
	params->dircheck = 0;
	params->usr_input = NULL;
	params->input1 = NULL;
	params->cmd = NULL;
	params->paths = NULL;
	params->heredoc = NULL;
	params->i = 0;
	params->fd_in = 0;
	params->fd_out = 0;
	params->envp = init_env(envp);
	return (1);
}

static int	minishell(t_minishell *p, char *input)
{
	input = get_input(p, NULL, NULL, 0);
	if (!input)
		return (1);
	if (!*input)
		return (-1);
	if (!directory_handler(p, input, 0))
		return (-1);
	p->usr_input = input;
	p->exit_status = g_es;
	p->split_input = ft_shell_split(p, p->usr_input, 32);
	if (!p->split_input || !*p->split_input)
		return (-1);
	if (!ft_strncmp(p->split_input[0], "exit", 5))
		return (builtin_exit(p->split_input, -1));
	add_history(input);
	signal(SIGINT, sigint_handler_b);
	run_commands(p, p->split_input, 0, 0);
	g_es = p->exit_status;
	free_everything(p, NULL, NULL);
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	p;
	int			es;

	es = -1;
	argc = 0;
	argv = NULL;
	init_params(&p, envp);
	while (es < 0)
	{
		init_signals();
		es = minishell(&p, NULL);
	}
	free_everything(&p, p.envp, NULL);
	exit(es);
}