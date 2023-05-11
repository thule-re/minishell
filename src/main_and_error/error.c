/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:49:29 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/02 13:15:42 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handler(char *s, t_minishell *params)
{
	perror(s);
	if (params)
		free_everything(params, params->envp);
	exit(1);
}

void	file_error(char *s, int fd, int error_type, t_minishell *params)
{
	if (fd != -1)
		write(fd, "       0\n", 9);
	write(STDERR_FILENO, "minishell: ", 11);
	perror(s);
	g_es = error_type;
	params->fd_in = 0;
	params->fd_out = 0;
}

void	cmd_error(char *str, t_minishell *params)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (!ft_getenv("PATH", *params->envp))
		ft_putstr_fd(": no such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	free_everything(params, params->envp);
	exit(127);
}

void	malloc_error(t_minishell *params, int do_free, int do_exit)
{
	if (params->usr_input || do_exit)
		ft_putstr_fd("minishell: Memory allocation failed: out of memory\n", 2);
	if (do_free)
		free_everything(params, NULL);
	if (do_exit)
	{
		free_everything(params, params->envp);
		exit(1);
	}
}
