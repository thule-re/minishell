/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:02:25 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/17 17:44:38 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}

void	shift_array(char **arr, int i)
{
	char	*to_free;

	to_free = arr[i];
	while (arr[i])
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[i] = NULL;
	free(to_free);
}

int	check_access(char **input)
{
	while (*input)
	{
		if (access(*input, R_OK) == 0)
			return (1);
		input++;
	}
	return (0);
}
