/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:50:04 by treeps            #+#    #+#             */
/*   Updated: 2023/05/11 18:58:38 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*env_add_key(t_env *envp, char **key_val)
{
	while (envp)
	{
		if (!ft_strncmp(envp->key, key_val[0], ft_strlen(key_val[0]) + 1))
		{
			free(envp->value);
			if (!key_val[1])
				envp->value = NULL;
			else
				envp->value = ft_strdup(key_val[1]);
			return (envp->value);
		}
		if (!envp->next)
			break ;
		envp = envp->next;
	}
	envp->next = new_env_node(key_val);
	return (envp->next->value);
}

static char	**get_key_val(char *input)
{
	char	**key_val;
	char	*loc;

	key_val = (char **)ft_calloc(3, sizeof(char *));
	if (!key_val)
		return (NULL);
	if (!ft_strchr(input, '=') || input[0] == '=')
		key_val[0] = ft_strdup(input);
	else
	{
		loc = ft_strchr(input, '=');
		*loc = 0;
		key_val[0] = ft_strdup(input);
		if (!key_val[0])
			return (NULL);
		if (*(loc + 1))
			key_val[1] = ft_strdup(loc + 1);
		else
			key_val[1] = ft_calloc(1, 1);
	}
	if (!key_val[0] && !key_val[1])
		return (NULL);
	if (!key_val[0])
		return (free(key_val[1]), NULL);
	return (key_val);
}

static int	is_valid(char *input, char *key)
{
	int	ret;

	ret = 1;
	if (ft_isdigit(key[0]) || !*key)
		ret = 0;
	while (*key)
	{
		if (ft_strchr("~-@*!+\\{}[]^:=;+", *key))
			ret = 0;
		key++;
	}
	if (!ret)
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd("' is not a valid identifier\n", 2);
	}
	return (ret);
}

int	export(t_minishell *p, int forked)
{
	char	**key_val;
	int		i;
	int		code;

	code = 0;
	if (!p->input1[1])
		return (display_export(p, forked), ft_return(p, 0, forked));
	i = 1;
	while (p->input1[i])
	{
		key_val = get_key_val(p->input1[i]);
		if (!key_val)
			return (ft_return(p, 1, forked));
		if (!is_valid(p->input1[i], key_val[0]))
			code = 1;
		else
			env_add_key(*p->envp, key_val);
		if (!(*p->envp)->key)
			return (ft_return(p, 1, forked));
		i++;
		free_arr(key_val);
	}
	return (ft_return(p, code, forked));
}
