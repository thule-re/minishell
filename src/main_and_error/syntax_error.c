/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:48:50 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/03 11:21:29 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_error(char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
}

int	check_syntax(char **arr)
{
	int	i;

	if (!ft_strncmp(arr[0], "|", 2))
		return (parse_error(arr[0]), 1);
	i = 0;
	while (arr[i])
	{
		if (!ft_strncmp(arr[i], "||", 2))
			return ((parse_error("||")), 1);
		if (!ft_strncmp(arr[i], "<<>", 3) || !ft_strncmp(arr[i], "<>", 2))
			return ((parse_error(">")), 1);
		if (*arr[i] == '>' && arr[i][1] == '<')
			return ((parse_error(">")), 1);
		if (!ft_strncmp(arr[i], "<<<<", 4))
			return ((parse_error("<<")), 1);
		if (!ft_strncmp(arr[i], "<<<", 3) || !ft_strncmp(arr[i], ">><", 3))
			return ((parse_error("<")), 1);
		if (!ft_strncmp(arr[i], ">>>>", 4))
			return ((parse_error(">>")), 1);
		if (!ft_strncmp(arr[i], ">>>", 3))
			return ((parse_error(">")), 1);
		i++;
	}
	return (0);
}
