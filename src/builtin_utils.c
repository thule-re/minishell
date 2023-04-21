/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsbur>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:02:56 by treeps            #+#    #+#             */
/*   Updated: 2023/04/14 12:47:14 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_return(t_pipehelper *p, int code, int forked)
{
	if (forked)
		exit(code);
	p->exit_status = code;
	return (0);
}

int	run_builtin(t_pipehelper *p, int forked)
{
	if (ft_strncmp("echo", p->input1[0], 5) == 0)
		return (echo(p, forked));
	if (ft_strncmp("cd", p->input1[0], 3) == 0)
		return (cd(p, forked));
	if (ft_strncmp("pwd", p->input1[0], 4) == 0)
		return (pwd(p, forked));
	if (ft_strncmp("export", p->input1[0], 7) == 0)
		return (export(p, forked));
	if (ft_strncmp("unset", p->input1[0], 6) == 0)
		return (unset(p, forked));
	if (ft_strncmp("env", p->input1[0], 4) == 0)
		return (env(p, forked));
	return (1);
}
