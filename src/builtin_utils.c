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
	p->exit_status = code;
	if (forked)
		exit(code);
	return (0);
}

int	run_builtin(t_pipehelper *p, int forked)
{
	if (ft_strncmp("echo", p->input1[0], 5) == 0)
		echo(p, forked);
	else if (ft_strncmp("cd", p->input1[0], 3) == 0)
		cd(p, forked);
	else if (ft_strncmp("pwd", p->input1[0], 4) == 0)
		pwd(p, forked);
	else if (ft_strncmp("export", p->input1[0], 7) == 0)
		export(p, forked);
	else if (ft_strncmp("unset", p->input1[0], 6) == 0)
		unset(p, forked);
	else if (ft_strncmp("env", p->input1[0], 4) == 0)
		env(p, forked);
	else
		return (0);
	return (1);
}
