/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:11:33 by treeps            #+#    #+#             */
/*   Updated: 2023/05/01 15:39:53 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
