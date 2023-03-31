/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:48:29 by awilliam          #+#    #+#             */
/*   Updated: 2023/03/31 18:59:54 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	next_one(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == 34)
			return (s[i]);
		if (s[i] == 39)
			return (s[i]);
		if (s[i] == ' ')
			return (s[i]);
		i++;
	}
	return (0);
}

void	free_strings(char **result, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(result[i]);
		i++;
	}
	free(result);
}
