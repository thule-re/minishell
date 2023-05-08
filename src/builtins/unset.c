/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:11:33 by treeps            #+#    #+#             */
/*   Updated: 2023/05/08 15:47:25 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid(char *key)
{
	int		ret;
	char	*tmp;

	tmp = key;
	ret = 1;
	if (ft_isdigit(key[0]))
		ret = 0;
	while (*key)
	{
		if (ft_strchr("=~-@*!+\\{}[]^;+", *key))
			ret = 0;
		key++;
	}
	if (!ret)
	{
		ft_putstr_fd("minishell: unset: '", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd("' is not a valid identifier\n", 2);
	}
	return (ret);
}

static void	clean_env(t_env **envp)
{
	t_env	*tmp;
	t_env	*cur;

	if (!envp)
		return ;
	if (!(*envp)->key)
	{
		tmp = (*envp)->next;
		free((*envp));
		envp = &tmp;
	}
	cur = *envp;
	while (cur->next)
	{
		if (!cur->next->key)
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			free(tmp);
			return ;
		}
		cur = cur->next;
	}
}

int	unset(t_minishell *p, int forked)
{
	t_env	*env_var;

	if (forked)
		return (ft_return(p, 0, forked));
	env_var = ft_getenvp(p->input1[1], *p->envp);
	if (p->input1[1] && !is_valid(p->input1[1]))
		return (ft_return(p, 1, forked));
	if (!env_var)
		return (ft_return(p, 0, forked));
	if (env_var == (*p->envp))
	{
		free((*p->envp)->key);
		free((*p->envp)->value);
		env_var = (*p->envp)->next;
		free(*p->envp);
		*p->envp = env_var;
		return (ft_return(p, 0, forked));
	}
	free(env_var->value);
	env_var->value = NULL;
	free(env_var->key);
	env_var->key = NULL;
	clean_env(p->envp);
	return (ft_return(p, 0, forked));
}
