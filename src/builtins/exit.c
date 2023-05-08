/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:40:43 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/01 12:35:45 by awilliam         ###   ########.fr       */
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
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
}

static void	numeric_argument(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	builtin_exit(t_minishell *p)
{
	int	i;

	i = 0;
	if (!p->input1[1])
	{
		ft_putstr_fd("exit\n", 2);
		return (ft_exit(p, 0));
	}
	if (p->input1[2] && !ft_isalpha(p->input1[1][0]))
		return (to_many_arguments(), ft_exit(p, 1));
	if (p->input1[3])
		return (to_many_arguments(), ft_exit(p, 255));
	if (ft_strchr("-+", p->input1[1][i]))
		i++;
	while (p->input1[1][i])
	{
		if (!ft_isdigit(p->input1[1][i]))
			return (numeric_argument(p->input1[1]), ft_exit(p, 255));
		i++;
	}
	if (ft_strlen(p->input1[1]) > 9 || ft_atoi(p->input1[1]) == -1)
		return (ft_exit(p, 255));
	return (ft_exit(p, ft_atoi(p->input1[1])));
}
