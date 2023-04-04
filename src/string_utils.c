/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:16:03 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/04 11:57:23 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_wordsearch(char *str, char *to_find)
{
	char	*tmp;
	int		i;

	if (!str || !to_find || !*to_find)
		return (0);
	while (*str)
	{
		i = 0;
		tmp = str;
		while (*tmp == to_find[i] && to_find[i])
		{
			tmp++;
			i++;
		}
		if (!to_find[i])
			return ((char *)str);
		str++;
	}
	return (0);
}

char	**get_path(char **envp)
{
	char	**path;

	if (*envp == NULL)
		return (ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:", ':'));
	path = NULL;
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (ft_wordsearch(*envp, "PATH"))
			path = ft_split(ft_wordsearch(*envp, "PATH") + 5, ':');
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

	if (access(cmd_str, X_OK) != -1)
		return (ft_strdup(cmd_str));
	if (!cmd_str)
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
	else
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
