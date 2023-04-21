/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsbur>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:03:34 by treeps            #+#    #+#             */
/*   Updated: 2023/04/18 13:03:41 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **envp)
{
	t_env	*next;
	t_env	*cur;

	cur = *envp;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(envp);
}

t_env	*new_env_node(char **key_val)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key_val[0]);
	if (!new_node->key)
		return (free(new_node), NULL);
	new_node->value = ft_strdup(key_val[1]);
	if (!new_node->value)
		return (free(new_node->key), free(new_node), NULL);
	new_node->next = NULL;
	return (new_node);
}

t_env	**init_env(char **static_env)
{
	t_env	**envp;
	t_env	*curr;
	char	**key_val;

	if (static_env == NULL)
		return (NULL);
	key_val = ft_split(*static_env, '=');
	if (!key_val)
		return (NULL);
	envp = (t_env **)ft_calloc(1, sizeof(t_env *));
	if (!envp)
		return (NULL);
	*envp = new_env_node(key_val);
	free_arr(key_val);
	if (!*envp)
		return (NULL);
	static_env++;
	curr = *envp;
	while (*static_env)
	{
		key_val = ft_split(*static_env, '=');
		curr->next = new_env_node(key_val);
		free_arr(key_val);
		if (!curr->next)
			return (free_env(envp), NULL);
		static_env++;
		curr = curr->next;
	}
	return (envp);
}
