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

char	*ft_getenv(char *str, char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(str, *envp, ft_strlen(str)) == 0)
			return (*envp + ft_strlen(str) + 1);
		envp++;
	}
	return (NULL);
}

int	run_builtin(char **cmd_str)
{
	// if (ft_strncmp("echo", cmd_str, 4) == 0)
	// 	return (echo(cmd_str));
	// if (ft_strncmp("cd", cmd_str, 2) == 0)
	// 	return (cd(cmd_str));
	// if (ft_strncmp("pwd", cmd_str, 3) == 0)
	// 	return (pwd());
	// if (ft_strncmp("export", cmd_str, 6) == 0)
	// 	return (export(cmd_str));
	// if (ft_strncmp("unset", cmd_str, 5) == 0)
	// 	return (unset(cmd_str));
	// if (ft_strncmp("env", cmd_str, 3) == 0)
	// 	return (env());
	cmd_str = (void *)cmd_str;
	return (0);
}
