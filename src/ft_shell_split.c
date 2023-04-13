/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:31:14 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/13 13:37:19 by awilliam         ###   ########.fr       */
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
			count++;
			while (str[i] != apo_type)
				i++;
		}
		if (str[i] == c && str[i + 1] != c && !is_apo(str[i + 1]))
			count++;
		if (str[i + 1])
			i++;
	}
	return (count);
}

int	mod_ft_strlen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static int	shell_split_helper(char *s, char **result, int i)
{
	int		len;

	if (!is_apo(*s))
		len = mod_ft_strlen(s, next_one(s)) + 1;
	else
		len = mod_ft_strlen(s + 1, *s) + 3;
	result[i] = malloc(len);
	if (result[i])
		ft_strlcpy(result[i], s, len);
	if (is_apo(*s))
		len--;
	return (len);
}

char	**ft_shell_split(char *s, char c)
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
	return (reformat_inputs(result));
}
