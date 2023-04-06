/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:02:25 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/06 16:55:33 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		if (arr[i])
			free (arr[i]);
		i++;
	}
	if (arr)
		free(arr);
	return ;
}

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
	free(arr[i]);
	free(to_free);
}
