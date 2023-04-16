/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:49:29 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/16 11:56:14 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_arrs(t_pipehelper *params)
{
	if (params->cmd)
		free(params->cmd);
	if (params->paths)
		free_arr(params->paths);
	if (params->input1)
		free_arr(params->input1);
	params->cmd = NULL;
	params->input1 = NULL;
	params->paths = NULL;
}

void	error_handler(char *s, t_pipehelper *params)
{
	perror(s);
	if (params)
		free_arrs(params);
	exit(1);
}

void	file_error(char *s, int fd, int error_type, t_pipehelper *params)
{
	if (fd != -1)
		write(fd, "       0\n", 9);
	write(STDERR_FILENO, "minishell: ", 11);
	perror(s);
	if (params)
		free_arrs(params);
	exit(error_type);
}

void	cmd_error(char *str, t_pipehelper *params)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	if (params)
		free_arrs(params);
	exit(127);
}
