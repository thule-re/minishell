/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsbur>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:06:34 by treeps            #+#    #+#             */
/*   Updated: 2023/04/17 12:43:52 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	perror(str);
	return (1);
}

static int	update_env(t_pipehelper *p, char *pwd_before)
{
	char	**old_pwd;
	char	**cur_pwd;
	char	*tmp;
	char	new_pwd[MAXPATHLEN];

	getcwd(new_pwd, MAXPATHLEN);
	old_pwd = ft_getenvp("OLDPWD", p->envp);
	if (*old_pwd)
	{
		free(*old_pwd);
		tmp = ft_strjoin("OLDPWD=", pwd_before);
		*old_pwd = ft_strdup(tmp);
		free(tmp);
	}
	cur_pwd = ft_getenvp("PWD", p->envp);
	if (*cur_pwd)
	{
		free(*cur_pwd);
		tmp = ft_strjoin("PWD=", new_pwd);
		*cur_pwd = ft_strdup(tmp);
		free(tmp);
	}
	return (0);
}

int	cd(t_pipehelper *p, int forked)
{
	char	*path;
	char	*tmp;
	char	pwd_before[MAXPATHLEN];

	getcwd(pwd_before, MAXPATHLEN);
	if (!p->input1[1])
		return (ft_return(p, 0, forked));
	if (access(p->input1[1], X_OK) != 0)
	{
		tmp = ft_strjoin(ft_getenv("PWD", p->envp), "/");
		if (strncmp(p->input1[1], "./", 2) == 0)
			path = ft_strjoin(tmp, p->input1[1] + 2);
		else
			path = ft_strjoin(tmp, p->input1[1]);
		free(tmp);
	}
	else
		path = ft_strdup(p->input1[1]);
	if (access(path, X_OK) != 0)
	{
		free(path);
		return (ft_return(p, cd_error(p->input1[1]), forked));
	}
	if (chdir(path) == -1)
	{
		free(path);
		return (ft_return(p, cd_error(p->input1[1]), forked));
	}
	free(path);
	update_env(p, pwd_before);
	return (0);
}
