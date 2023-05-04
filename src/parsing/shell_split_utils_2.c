/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:46:22 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/04 14:21:13 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:14:01 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/04 11:28:09 by awilliam         ###   ########.fr       */
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
	ft_strlcpy(tmp2, s, i + 1);
	to_free = tmp;
	tmp = ft_strjoin(tmp2, tmp);
	free(to_free);
	free(tmp2);
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
	return (ret);
}

char	**reformat_inputs(t_minishell *p, char **arr, int i)
{
	while (arr[i])
	{
		if (!is_special_char(arr[i]))
			arr[i] = remove_apos(p, arr[i], NULL, 0);
		if (special_no_quotes(arr[i], "<>|"))
		{
			if (!arr[i + 1] || !*(arr[i + 1]))
			{
				if (arr[i][0] == '|')
					return (parse_error("|"), NULL);
				else
					return (parse_error("newline"), NULL);
			}
		}
		i++;
	}
	return (arr);
}
