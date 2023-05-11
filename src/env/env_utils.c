/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:03:34 by treeps            #+#    #+#             */
/*   Updated: 2023/05/03 19:00:14 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *str, t_env *envp)
{
	if (str == NULL)
		return (NULL);
	while (envp)
	{
		if (!envp->key)
		{
			envp = envp->next;
			continue ;
		}
		if (ft_strncmp(str, envp->key, ft_strlen(str) + 1) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

t_env	*ft_getenvp(char *str, t_env *envp)
{
	if (str == NULL)
		return (NULL);
	while (envp)
	{
		if (!envp->key)
		{
			envp = envp->next;
			continue ;
		}
		if (ft_strncmp(str, envp->key, ft_strlen(str) + 1) == 0)
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

void	free_env(t_env **envp)
{
	t_env	*next;
	t_env	*cur;

	if (!envp)
		return ;
	cur = *envp;
	while (cur)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
	free(envp);
}

t_env	*new_env_node(char **key_val)
{
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key_val[0]);
	if (!new_node->key)
		return (free(new_node), NULL);
	if (key_val[1])
	{
		new_node->value = ft_strdup(key_val[1]);
		if (!new_node->value)
			return (free(new_node->key), free(new_node), NULL);
	}
	new_node->next = NULL;
	return (new_node);
}
