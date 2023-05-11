/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:44:39 by treeps            #+#    #+#             */
/*   Updated: 2023/05/11 13:01:00 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	**make_list(t_env *envp)
{
	t_env	**list;
	int		i;

	i = 0;
	list = ft_calloc(ft_getenvlen(envp) + 1, sizeof(t_env *));
	while (envp)
	{
		list[i] = envp;
		envp = envp->next;
		i++;
	}
	return (list);
}

static t_env	**sort_list(t_env **list)
{
	t_env	*tmp;
	int		len;
	int		i;
	int		j;

	i = -1;
	while (list[++i])
	{
		j = i;
		len = ft_strlen(list[i]->key);
		while (list[++j])
		{
			if (ft_strncmp(list[i]->key, list[j]->key, len) > 0)
			{
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
		}
	}
	return (list);
}

void	display_export(t_minishell *p, int forked)
{
	t_env	**cur;
	int		fd;
	int		i;

	i = -1;
	fd = STDOUT_FILENO;
	if (!forked && p->fd_out)
		fd = p->fd_out;
	cur = sort_list(make_list(*p->envp));
	while (cur[++i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(cur[i]->key, fd);
		if (!cur[i]->value)
			ft_putstr_fd("\n", fd);
		else if (!*cur[i]->value)
			ft_putstr_fd("=''\n", fd);
		else
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(cur[i]->value, fd);
			ft_putstr_fd("\"\n", fd);
		}
	}
	free(cur);
}
