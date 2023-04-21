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
		if (envp->value)
		{
			ft_putstr_fd(envp->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(envp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		envp = envp->next;
	}
	return (ft_return(p, 0, forked));
}
