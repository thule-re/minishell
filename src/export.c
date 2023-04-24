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

static void	env_add_back(t_env *envp, char **key_val)
{
	while (envp->next)
		envp = envp->next;
	envp->next = new_env_node(key_val);
}

static void	update_node(t_env *node, char **key_val)
{
	free(node->value);
	if (!key_val[1])
		node->value = NULL;
	else
		node->value = ft_strdup(key_val[1]);
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
		else if (input[1])
			key_val[1] = ft_strdup(input[1]);
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
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(cur->key, 1);
		if (!cur->value)
			ft_putstr_fd("\n", 1);
		else if (!*cur->value)
			ft_putstr_fd("=''\n", 1);
		else
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(cur->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		cur = cur->next;
	}
}

int	export(t_pipehelper *p, int forked)
{
	char	**key_val;
	t_env	*cur;

	if (!p->input1[1])
	{
		display_export(p);
		return (ft_return(p, 0, forked));
	}
	key_val = get_key_val(&p->input1[1]);
	if (!key_val)
		return (ft_return(p, 1, forked));
	cur = *p->envp;
	while (cur)
	{
		if (!ft_strncmp(cur->key, key_val[0], ft_strlen(key_val[0])))
		{
			update_node(cur, key_val);
			return (free_arr(key_val), ft_return(p, 0, forked));
		}
		cur = cur->next;
	}
	env_add_back(*p->envp, key_val);
	return (free_arr(key_val), ft_return(p, 0, forked));
}
