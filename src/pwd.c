/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsbur>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:20:53 by treeps            #+#    #+#             */
/*   Updated: 2023/04/17 15:17:21 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_pipehelper *p, int forked)
{
	char	*pwd;

	pwd = ft_getenv("PWD", *p->envp);
	if (pwd)
		ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	return (ft_return(p, 0, forked));
}
