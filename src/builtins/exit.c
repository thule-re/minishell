/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:40:43 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/01 12:35:45 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_exit(char **parsed_input, int ret)
{
	int	i;

	i = 0;
	if (!parsed_input[1])
	{
		ft_putstr_fd("exit\n", 2);
		ret = 0;
	}
	while (parsed_input[1] && parsed_input[1][i])
	{
		if (!ft_isdigit(parsed_input[1][i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(parsed_input[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			ret = 255;
			break ;
		}
		i++;
	}
	if (ret == -1)
		ret = ft_atoi(parsed_input[1]);
	return (ret);
}
