/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:21:34 by treeps            #+#    #+#             */
/*   Updated: 2023/05/08 11:21:38 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*add_special_node(char **key_val)
{
	if (!ft_strncmp(key_val[0], "SHLVL", 6))
	{
		if (!key_val[1])
			return (new_env_node(key_val));
		free(key_val[1]);
		key_val[1] = ft_itoa(ft_atoi(key_val[1]) + 1);
	}
	return (new_env_node(key_val));
}

t_env	**init_env(char **static_env)
{
	t_env	**envp;
	t_env	*curr;
	char	**key_val;

	key_val = ft_split(*static_env, '=');
	envp = (t_env **)ft_calloc(1, sizeof(t_env *));
	if (!key_val || !envp)
		return (NULL);
	*envp = new_env_node(key_val);
	if (!*envp)
		return (NULL);
	curr = *envp;
	while (*++static_env)
	{
		free_arr(key_val);
		key_val = ft_split(*static_env, '=');
		if (!key_val)
			return (free_env(envp), NULL);
		curr->next = add_special_node(key_val);
		if (!curr->next)
			return (free_env(envp), NULL);
		curr = curr->next;
	}
	return (free_arr(key_val), envp);
}
