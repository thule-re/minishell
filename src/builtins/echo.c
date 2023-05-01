/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:03:34 by treeps            #+#    #+#             */
/*   Updated: 2023/05/01 16:45:47 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_option_n(char *str)
{
	int	has_option;

	has_option = 0;
	if (*str != '-')
		return (0);
	while (*(++str) == 'n')
		has_option = 1;
	if (!*str && has_option)
		return (1);
	return (0);
}

int	echo(t_minishell *p, int forked)
{
	int	i;
	int	fd;
	int	has_n;

	fd = STDOUT_FILENO;
	if (!forked && p->fd_out)
		fd = p->fd_out;
	has_n = 0;
	i = 1;
	while (p->input1[i] && has_option_n(p->input1[i]))
	{
		has_n = 1;
		i++;
	}
	while (p->input1[i])
	{
		ft_putstr_fd(p->input1[i++], fd);
		if (p->input1[i])
			ft_putstr_fd(" ", fd);
	}
	if (!has_n)
		ft_putstr_fd("\n", fd);
	return (ft_return(p, 0, forked));
}
