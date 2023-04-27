/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsbur>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:50:04 by treeps            #+#    #+#             */
/*   Updated: 2023/04/17 17:53:08 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_add_key(t_env *envp, char **key_val)
{
	while (envp)
	{
		if (!ft_strncmp(envp->key, key_val[0], ft_strlen(key_val[0])))
		{
			free(envp->value);
			if (!key_val[1])
				envp->value = NULL;
			else
				envp->value = ft_strdup(key_val[1]);
			return ;
		}
		if (!envp->next)
			break ;
		envp = envp->next;
	}
	envp->next = new_env_node(key_val);
}

static char	**get_key_val(char **input)
{
	char	**key_val;
	char	**tmp;

	key_val = (char **)ft_calloc(3, sizeof(char *));
	if (!key_val)
		return (NULL);
	if (!ft_strchr(input[0], '='))
	{
		key_val[0] = ft_strdup(input[0]);
		return (key_val);
	}
	else
	{
		tmp = ft_split(input[0], '=');
		key_val[0] = ft_strdup(tmp[0]);
		if (tmp[1])
			key_val[1] = ft_strdup(tmp[1]);
		else
			key_val[1] = ft_calloc(1, 1);
		free_arr(tmp);
	}
	return (key_val);
}

static void	display_export(t_pipehelper *p)
{
	t_env	*cur;

	cur = *p->envp;
	while (cur)
	{
		if (!cur->value && !cur->key)
		{
			cur = cur->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", p->fd_out);
		ft_putstr_fd(cur->key, p->fd_out);
		if (!cur->value)
			ft_putstr_fd("\n", p->fd_out);
		else if (!*cur->value)
			ft_putstr_fd("=''\n", p->fd_out);
		else
		{
			ft_putstr_fd("=\"", p->fd_out);
			ft_putstr_fd(cur->value, p->fd_out);
			ft_putstr_fd("\"\n", p->fd_out);
		}
		cur = cur->next;
	}
}

int	export(t_pipehelper *p, int forked)
{
	char	**key_val;
	int		i;

	if (!p->input1[1])
	{
		display_export(p);
		return (ft_return(p, 0, forked));
	}
	i = 1;
	while (p->input1[i])
	{
		key_val = get_key_val(&p->input1[i]);
		if (!key_val)
			return (ft_return(p, 1, forked));
		env_add_key(*p->envp, key_val);
		i++;
	}
	return (free_arr(key_val), ft_return(p, 0, forked));
}
