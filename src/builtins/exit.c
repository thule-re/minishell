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

static int	to_many_arguments(int code)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (code);
}

static int	numeric_argument(char *str, int code)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (code);
}

int	builtin_exit(char **parsed_input)
{
	int	i;

	i = 0;
	if (!parsed_input[1])
	{
		ft_putstr_fd("exit\n", 2);
		return (0);
	}
	if (parsed_input[2] && !ft_isalpha(parsed_input[1][0]))
		return (to_many_arguments(1));
	if (parsed_input[3])
		return (to_many_arguments(255));
	if (ft_strchr("-+", parsed_input[1][i]))
		i++;
	while (parsed_input[1][i])
	{
		if (!ft_isdigit(parsed_input[1][i]))
			return (numeric_argument(parsed_input[1], 255));
		i++;
	}
	if (ft_strlen(parsed_input[1]) > 9 || ft_atoi(parsed_input[1]) == -1)
		return (255);
	return (ft_atoi(parsed_input[1]));
}
