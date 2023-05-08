/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:48:29 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/08 09:33:51 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	apo_count(char *str, char apo)
{
	int	count;

	count = 0;
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str == apo)
			count++;
		str++;
	}
	return (count);
}

int	is_apo(char c)
{
	if (c == 34 || c == 39)
		return (1);
	else
		return (0);
}

int	is_special_char(char *s)
{
	if (!(ft_strncmp("\"<\"", s, 4)))
		return (1);
	if (!(ft_strncmp("\"<<\"", s, 5)))
		return (1);
	if (!(ft_strncmp("\">\"", s, 4)))
		return (1);
	if (!(ft_strncmp("\">>\"", s, 5)))
		return (1);
	if (!(ft_strncmp("\"|\"", s, 5)))
		return (1);
	return (0);
}

char	*remove_apos(t_minishell *p, char *s, char *ret, int len)
{
	char	*s_part;
	char	*tmp;

	if (!s)
		return (NULL);
	tmp = s;
	while (*s)
	{
		if (!is_apo(*s))
			len = ft_strlenc(s, next_one(s, " \'\""));
		else
			len = ft_strlenc(s + 1, *s) + 2;
		s_part = malloc(len + 1);
		if (!s_part)
			return (malloc_error(p, 0, 0), NULL);
		ft_strlcpy(s_part, s, len + 1);
		s += len;
		if (*s == ' ')
			s++;
		if ((s_part[0] != 39 && ft_strchr(s_part, '$')))
			s_part = expand_variables(p, s_part, NULL, 0);
		else if (is_apo(s_part[0]))
			string_shift(s_part);
		ret = ft_strjoinf(ret, s_part);
		if (!ret)
			return (malloc_error(p, 0, 0), NULL);
	}
	return (free(tmp), ret);
}

char	**reformat_inputs(t_minishell *p, char **arr, int i)
{
	while (arr[i])
	{
		if (!is_special_char(arr[i]))
			arr[i] = remove_apos(p, arr[i], NULL, 0);
		if (!arr[i])
			return (malloc_error(p, 0, 0), NULL);
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
