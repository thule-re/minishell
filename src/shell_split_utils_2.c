/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:14:01 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/14 11:17:15 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	string_shift(char *s)
{
	while (*s)
	{
		*s = *(s + 1);
		s++;
	}
	*(s - 2) = 0;
}

static char	*append_var_helper(char *s, char *tmp, char *ret, int i)
{
	char	*tmp2;

	tmp2 = malloc(i + 1);
	ft_strlcpy(tmp2, s, i + 1);
	ret = ft_strjoin(ret, tmp2);
	free(tmp2);
	tmp2 = ret;
	ret = ft_strjoin(ret, tmp);
	free(tmp2);
	free(tmp);
	return (ret);
}

static char	*append_var(t_pipehelper *p, char *s, int i, char *ret)
{
	int		len;
	char	*tmp;
	char	*var;

	len = ft_strlenc(&s[i + 1], ' ') + 1;
	var = malloc(len);
	ft_strlcpy(var, &s[i + 1], len);
	if (s[i + 1] == '?')
		tmp = ft_itoa(p->exit_status);
	else
	{
		tmp = ft_getenv(var, *p->envp);
		if (!tmp)
			tmp = ft_strdup("");
		else
			tmp = ft_strdup(tmp);
	}
	free(var);
	return (append_var_helper(s, ret, tmp, i));
}

char	*expand_variables(t_pipehelper *p, char *s)
{
	int		i;
	char	*ret;
	char	*to_free;

	ret = NULL;
	if (*s == 34)
		string_shift(s);
	to_free = s;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			ret = append_var(p, s, i, ret);
			s += i;
			i = 0;
		}
		i++;
	}
	free(to_free);
	return (ret);
}
