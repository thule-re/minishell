/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsbur>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:03:34 by treeps            #+#    #+#             */
/*   Updated: 2023/04/21 18:03:37 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_pipehelper *p, int forked)
{
	int	i;

	i = 1;
	if (p->input1[1] && !ft_strncmp(p->input1[1], "-n", 3))
		i++;
	while (p->input1[i])
	{
		ft_putstr_fd(p->input1[i++], fd);
		if (p->input1[i])
			ft_putstr_fd(" ", fd);
	}
	if (!p->input1[1] || ft_strncmp(p->input1[1], "-n", 3) != 0)
		ft_putstr_fd("\n", fd);
	return (ft_return(p, 0, forked));
}
