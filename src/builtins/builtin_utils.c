/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:02:56 by treeps            #+#    #+#             */
/*   Updated: 2023/05/01 17:32:48 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_return(t_minishell *p, int code, int forked)
{
	p->exit_status = code;
	if (forked)
	{
		free_everything(p, p->envp);
		exit(code);
	}
	return (0);
}

int	run_builtin(t_minishell *p, int forked)
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
	else if (ft_strncmp("exit", p->input1[0], 5) == 0)
		builtin_exit(p, forked);
	else
		return (0);
	return (1);
}
