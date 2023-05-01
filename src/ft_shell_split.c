/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:31:14 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/01 12:28:02 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	word_count(char *str, char c, int i, int count)
{
	char	apo_type;

	if (!str || !*str)
		return (0);
	if (str[i] != c)
		count++;
	while (str[i + 1])
	{
		if (is_apo(str[i]) && apo_count(&str[i + 1], str[i]))
		{
			apo_type = str[i];
			i++;
			while (str[i] != apo_type)
				i++;
			i++;
		}
		if (str[i] == c && str[i + 1] != c)
			count++;
		if (str[i + 1])
			i++;
	}
	return (count);
}

static int	shell_split_helper(char *s, char **result, int i)
{
	int		len;

	len = 0;
	while (*(s + len) && *(s + len) != ' ')
	{
		if (!is_apo(*s))
			len += ft_strlenc(s, next_one(s));
		else
		{
			len += ft_strlenc(s + 1, *s) + 2;
			if (*(s + len - 1) == ' ')
				break ;
		}
	}
	result[i] = malloc(len + 1);
	if (result[i])
		ft_strlcpy(result[i], s, len + 1);
	return (len);
}

char	**ft_shell_split(t_minishell *p, char *s, char c)
{
	char	**result;
	int		i;
	int		count;

	i = 0;
	count = word_count(s, c, 0, 0);
	result = malloc((count + 1) * sizeof(char *));
	if (result == NULL)
		return (0);
	while (*s == c && *s)
		s++;
	while (*s && i < count)
	{
		s += shell_split_helper(s, result, i);
		if (!result[i] || !s)
		{
			free_strings(result, i);
			return (0);
		}
		while (*s == c && *s)
			s++;
		i++;
	}
	result[i] = 0;
	return (reformat_inputs(p, result));
}
