/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:23:21 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/02 12:48:32 by awilliam         ###   ########.fr       */
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
	params->pipefd = NULL;
	params->i = 0;
	params->fd_in = 0;
	params->fd_out = 0;
	params->envp = init_env(envp);
	if (!params->envp)
		malloc_error(params, 1, 1);
	return (1);
}

static int	minishell(t_minishell *p, char *input)
{
	input = get_input(p, NULL, NULL, 1);
	if (!input)
		return (1);
	if (!*input)
		return (free(input), -1);
	if (!directory_handler(p, input, 0))
		return (-1);
	p->usr_input = input;
	p->exit_status = g_es;
	add_history(input);
	p->split_input = ft_shell_split(p, p->usr_input, 32);
	if (!p->split_input || !*p->split_input || check_syntax(p->split_input))
		return (-1);
	if (!ft_strncmp(p->split_input[0], "exit", 5))
		return (builtin_exit(p->split_input, -1));
	signal(SIGINT, sigint_handler_b);
	run_commands(p, 0, 0, init_variables(p, p->split_input));
	g_es = p->exit_status;
	free_everything(p, NULL);
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	p;
	int			es;

	es = -1;
	if (argc)
		argc = 0;
	if (argv)
		argv = NULL;
	init_params(&p, envp);
	while (es < 0)
	{
		init_signals();
		es = minishell(&p, NULL);
	}
	free_everything(&p, p.envp);
	exit(es);
}
