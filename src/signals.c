/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:43:50 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/17 15:49:34 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler_a(int signum)
{
	signum += 0;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_es = 130;
}

void	sigint_handler_b(int signum)
{
	signum += 0;
	rl_replace_line("", 0);
	rl_on_new_line();
	g_es = 130;
}

void	sigquit_handler(int signum)
{
	int	do_nothing;

	rl_replace_line("", 0);
	rl_redisplay();
	do_nothing = 42;
	do_nothing += signum;
}

void	init_signals(void)
{
	signal(4, sigquit_handler);
	signal(SIGINT, sigint_handler_a);
	signal(SIGQUIT, sigquit_handler);
}

void	check_signals(t_pipehelper *p)
{
	if (WIFEXITED(p->exit_status) && !WIFSIGNALED(p->exit_status))
		p->exit_status = WEXITSTATUS(p->exit_status);
	if (WIFSIGNALED(p->exit_status) && p->exit_status == 2)
	{
		ft_putchar_fd('\n', 2);
		p->exit_status = 130;
	}	
}
