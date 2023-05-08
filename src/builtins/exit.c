/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:40:43 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/08 12:35:45 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_exit(t_minishell *p, int code)
{
	p->exit_status = code;
	free_everything(p, p->envp);
	exit(code);
}

static void	to_many_arguments(void)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
}

static void	numeric_argument(char *str)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	builtin_exit(t_minishell *p, int forked)
{
	int	i;
	int	exit_code;

	i = 0;
	if (!p->input1[1])
		return (ft_exit(p, 0));
	if (ft_strchr("+-", p->input1[1][0]))
		i++;
	while (p->input1[1][i])
	{
		if (!ft_isdigit(p->input1[1][i]))
			return (numeric_argument(p->input1[1]), ft_exit(p, 255));
		i++;
	}
	if (p->input1[2])
		return (to_many_arguments(), ft_return(p, 1, forked));
	exit_code = ft_atoi(p->input1[1]);
	ft_putstr_fd("exit\n", 2);
	if (exit_code < 0)
		return (ft_exit(p, 256 - ((exit_code * -1) % 256)));
	return (ft_exit(p, exit_code % 256));
}
