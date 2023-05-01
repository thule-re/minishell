/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:16:03 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/01 11:55:18 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_path(char **envp)
{
	char	**path;
	char	*tmp;

	if (*envp == NULL)
		return (ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:", ':'));
	path = NULL;
	if (!envp)
		return (NULL);
	while (*envp)
	{
		tmp = ft_strnstr(*envp, "PATH", ft_strlen(*envp));
		if (tmp)
			path = ft_split(tmp + 5, ':');
		envp++;
	}
	return (path);
}

char	*append_slash(char *path, char *str, char *c)
{
	char	*tmp;
	char	*ret_str;

	if (!path || !str)
		return (NULL);
	tmp = ft_strjoin(c, str);
	if (!tmp)
		return (NULL);
	ret_str = ft_strjoin(path, tmp);
	free (tmp);
	return (ret_str);
}

char	*get_command(char **paths, char *cmd_str)
{
	int		i;
	char	*cmd;

	if (!cmd_str)
		return (NULL);
	if (access(cmd_str, X_OK) != -1 || !*cmd_str)
		return (ft_strdup(cmd_str));
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd = append_slash(paths[i], cmd_str, "/");
		if (!cmd)
			return (NULL);
		if (access(cmd, F_OK) != -1)
			break ;
		ft_bzero(cmd, ft_strlen(cmd));
		if (cmd)
			free(cmd);
		cmd = NULL;
		i++;
	}
	if (cmd)
		return (cmd);
	return (ft_strdup(cmd_str));
}

void	strshift(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}

int	ft_strlenc(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
