/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:42:35 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/01 12:28:01 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	directory_print(void *dir)
{
	if (dir)
	{
		ft_putstr_fd(": is a directory\n", 2);
		g_es = 126;
	}
	else
	{
		ft_putstr_fd(": no such file or directory\n", 2);
		g_es = 127;
	}
}

int	directory_handler(t_minishell *p, char *input, char c)
{
	void	*dir;

	p->dircheck = 0;
	c = input[(ft_strlenc(input, ' '))];
	input[(ft_strlenc(input, ' '))] = 0;
	dir = opendir(input);
	if (dir)
		p->dircheck = 1;
	if (ft_strlenc(input, '/') >= ft_strlenc(input, ' '))
		free(dir);
	else if ((access(input, F_OK) == -1) || dir)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input, 2);
		input[(ft_strlen(input))] = c;
		directory_print(dir);
		if (dir)
			closedir(dir);
		free(input);
		input = NULL;
		return (0);
	}
	input[(ft_strlen(input))] = c;
	return (1);
}
