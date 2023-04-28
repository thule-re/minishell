/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: treeps <treeps@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:07:12 by treeps            #+#    #+#             */
/*   Updated: 2023/04/27 16:07:14 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_getenvlen(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static char	*ft_join_key_val(t_env *env)
{
	char	*str;
	int		key_len;
	int		val_len;
	int		len;

	key_len = ft_strlen(env->key);
	val_len = ft_strlen(env->value);
	len = key_len + val_len;
	if (env->value)
		len += 4;
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (NULL);
	ft_memmove(str, env->key, key_len);
	if (env->value)
	{
		str[key_len] = '=';
		str[key_len + 1] = '\"';
		ft_memmove(str + key_len + 2, env->value, val_len);
		str[key_len + val_len + 3] = '\"';
	}
	return (str);
}

char	**export_env(t_env *env)
{
	char	**res_env;
	int		i;

	i = 0;
	res_env = ft_calloc(ft_getenvlen(env) + 1, sizeof(char *));
	if (!res_env)
		return (NULL);
	while (env)
	{
		res_env[i] = ft_join_key_val(env);
		if (!res_env[i])
			return (free_arr(res_env), NULL);
		i++;
		env = env->next;
	}
	return (res_env);
}
