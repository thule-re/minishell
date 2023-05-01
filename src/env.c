/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:51:04 by treeps            #+#    #+#             */
/*   Updated: 2023/05/01 12:28:02 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_minishell *p, int forked)
{
	t_env	*envp;
	int		fd;

	fd = STDOUT_FILENO;
	if (!forked && p->fd_out != 0)
		fd = p->fd_out;
	envp = *p->envp;
	while (envp)
	{
		if (envp->value && *envp->value)
		{
			ft_putstr_fd(envp->key, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(envp->value, fd);
			ft_putstr_fd("\n", fd);
		}
		envp = envp->next;
	}
	return (ft_return(p, 0, forked));
}
