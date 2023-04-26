/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:51:04 by treeps            #+#    #+#             */
/*   Updated: 2023/04/12 14:13:40 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_pipehelper *p, int forked)
{
	t_env	*envp;

	envp = *p->envp;
	while (envp)
	{
		if (envp->value && *envp->value)
		{
			ft_putstr_fd(envp->key, p->fd_out);
			ft_putstr_fd("=", p->fd_out);
			ft_putstr_fd(envp->value, p->fd_out);
			ft_putstr_fd("\n", p->fd_out);
		}
		envp = envp->next;
	}
	return (ft_return(p, 0, forked));
}
