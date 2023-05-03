/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:06:34 by treeps            #+#    #+#             */
/*   Updated: 2023/05/03 19:06:35 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	perror(str);
	return (1);
}

static int	update_env(t_minishell *p, char *pwd_before)
{
	t_env	*old_pwd;
	t_env	*cur_pwd;
	char	new_pwd[MAXPATHLEN];

	getcwd(new_pwd, MAXPATHLEN);
	old_pwd = ft_getenvp("OLDPWD", *p->envp);
	if (old_pwd)
	{
		free(old_pwd->value);
		old_pwd->value = ft_strdup(pwd_before);
	}
	cur_pwd = ft_getenvp("PWD", *p->envp);
	if (cur_pwd)
	{
		free(cur_pwd->value);
		cur_pwd->value = ft_strdup(new_pwd);
	}
	return (0);
}

int	cd(t_minishell *p, int forked)
{
	char	*path;
	char	*tmp;
	char	pwd_before[MAXPATHLEN];

	getcwd(pwd_before, MAXPATHLEN);
	if (!p->input1[1])
		path = ft_strdup(ft_getenv("HOME", *p->envp));
	else if (access(p->input1[1], X_OK) != 0)
	{
		tmp = ft_strjoin(ft_getenv("PWD", *p->envp), "/");
		if (!tmp)
			return (ft_return(p, 1, forked));
		if (strncmp(p->input1[1], "./", 2) == 0)
			path = ft_strjoin(tmp, p->input1[1] + 2);
		else
			path = ft_strjoin(tmp, p->input1[1]);
		free(tmp);
	}
	else
		path = ft_strdup(p->input1[1]);
	if (chdir(path) == -1)
		return (free(path), ft_return(p, cd_error(p->input1[1]), forked));
	free(path);
	update_env(p, pwd_before);
	return (0);
}
