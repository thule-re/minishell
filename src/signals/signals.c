/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:43:50 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/04 18:18:13 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler_a(int signum)
{
	g_es = signum;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_es = 130;
}

void	sigint_handler_b(int signum)
{
	g_es = signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	g_es = 130;
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler_a);
	signal(SIGQUIT, SIG_IGN);
}

char	*exit_signal(void)
{
	ft_putstr_fd("\033[F", 2);
	put_prompt(1, 0, NULL, NULL);
	ft_putstr_fd("exit\n", 2);
	return (NULL);
}

void	check_signals(t_minishell *p)
{
	if (WIFEXITED(p->exit_status) && !WIFSIGNALED(p->exit_status))
		p->exit_status = WEXITSTATUS(p->exit_status);
	if (WIFSIGNALED(p->exit_status) && p->exit_status == 2)
	{
		ft_putchar_fd('\n', 2);
		p->exit_status = 130;
	}	
}
