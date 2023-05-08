/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsbur>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:20:53 by treeps            #+#    #+#             */
/*   Updated: 2023/05/01 12:28:02 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_minishell *p, int forked)
{
	int		fd;
	char	pwd[MAXPATHLEN];

	getcwd(pwd, MAXPATHLEN);
	fd = STDOUT_FILENO;
	if (!forked && p->fd_out)
		fd = p->fd_out;
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	return (ft_return(p, 0, forked));
}
