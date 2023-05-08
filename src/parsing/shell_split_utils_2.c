/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:14:01 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/08 09:34:23 by awilliam         ###   ########.fr       */
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

static char	*append_var_helper(char *s, char *ret, char *tmp, int i)
{
	char	*tmp2;
	char	*to_free;

	tmp2 = malloc(i + 1);
	if (!tmp2)
		return (NULL);
	ft_strlcpy(tmp2, s, i + 1);
	to_free = tmp;
	tmp = ft_strjoin(tmp2, tmp);
	free(to_free);
	free(tmp2);
	if (!tmp)
		return (NULL);
	tmp2 = tmp;
	if (!ret)
		tmp = ft_strjoin(tmp, ret);
	else
		tmp = ft_strjoin(ret, tmp);
	free(tmp2);
	free(ret);
	return (tmp);
}

static char	*append_var(t_minishell *p, char *s, int i, char *ret)
{
	int		len;
	char	*tmp;
	char	*var;

	if (ft_isdigit(s[i + 1]))
		len = 2;
	else
		len = ft_strlenc(&s[i + 1], next_one(&s[i + 1], "\'\" /=\n")) + 1;
	var = malloc(len);
	if (!var)
		return (NULL);
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
	if (!tmp)
		return (NULL);
	return (append_var_helper(s, ret, tmp, i));
}

char	*expand_variables(t_minishell *p, char *s, char *ret, int i)
{
	char	*to_free;
	char	*tmp;

	if (*s == 34 && s != p->heredoc)
		string_shift(s);
	to_free = s;
	while (s[i])
	{
		if (s[i] == '$')
		{
			ret = append_var(p, s, i, ret);
			if (!ret)
				return (malloc_error(p, 0, 0), NULL);
			if (ft_isdigit(s[i + 1]))
				s += i + 2;
			else
				s += i + ft_strlenc(&s[i], next_one(&s[i], "\"\' /=\n"));
			i = -1;
		}
		i++;
	}
	tmp = ret;
	ret = ft_strjoin(ret, s);
	free(tmp);
	free(to_free);
	if (!ret)
		return (malloc_error(p, 0, 0), NULL);
	return (ret);
}

char	next_one(char *s, char *set)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (ft_strchr(set, s[i]))
			return (s[i]);
		i++;
	}
	return (0);
}
