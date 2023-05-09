/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:48:29 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/09 09:40:23 by awilliam         ###   ########.fr       */
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

static int	get_len(char *s)
{
	if (!is_apo(*s))
		return (ft_strlenc(s, next_one(s, " \'\"")));
	else
		return (ft_strlenc(s + 1, *s) + 2);
}

char	*remove_apos(t_minishell *p, char *s, char *ret, int len)
{
	char	*s_part;
	char	*tmp;

	tmp = s;
	while (*s)
	{
		len = get_len(s);
		s_part = malloc(len + 1);
		if (!s_part)
			return (malloc_error(p, 1, 0), NULL);
		ft_strlcpy(s_part, s, len + 1);
		s += len;
		if (*s == ' ')
			s++;
		if ((s_part[0] != 39 && ft_strchr(s_part, '$')))
			s_part = expand_variables(p, s_part, NULL, 0);
		else if (is_apo(s_part[0]))
			string_shift(s_part);
		if (!s_part)
			return (malloc_error(p, 1, 0), NULL);
		ret = ft_strjoinf(ret, s_part);
		if (!ret)
			return (malloc_error(p, 1, 0), NULL);
	}
	return (free(tmp), ret);
}

static int	is_variable(char *s)
{
	if (!s)
		return (0);
	if (ft_strchr(s, '$'))
		return (1);
	else
		return (0);
}

char	**reformat_inputs(t_minishell *p, int i, int var, char *tmp)
{
	while (p->split_input[i])
	{
		var = is_variable(p->split_input[i]);
		if (!is_special_char(p->split_input[i]))
			tmp = remove_apos(p, p->split_input[i], NULL, 0);
		if (tmp)
			p->split_input[i] = tmp;
		else
			return (NULL);
		if (special_no_quotes(p->split_input[i], "<>|"))
		{
			if (!p->split_input[i + 1] || !*(p->split_input[i + 1]))
			{
				if (p->split_input[i][0] == '|')
					return (parse_error(p, "|"), NULL);
				else
					return (parse_error(p, "newline"), NULL);
			}
		}
		if (!*p->split_input[i] && var)
			shift_array(p->split_input, i);
		else
			i++;
	}
	return (p->split_input);
}
