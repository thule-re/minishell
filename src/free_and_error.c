/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:49:29 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/01 12:28:02 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_arrs(t_minishell *params)
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

void	error_handler(char *s, t_minishell *params)
{
	perror(s);
	if (params)
		free_arrs(params);
	exit(1);
}

void	file_error(char *s, int fd, int error_type, t_minishell *params)
{
	if (fd != -1)
		write(fd, "       0\n", 9);
	write(STDERR_FILENO, "minishell: ", 11);
	perror(s);
	if (params)
		free_arrs(params);
	exit(error_type);
}

void	cmd_error(char *str, t_minishell *params)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (!ft_getenv("PATH", *params->envp))
		ft_putstr_fd(": no such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	if (params)
		free_arrs(params);
	exit(127);
}

void	free_everything(t_minishell *p, char **parsed_input, char *input)
{
	free_arrs(p);
	if (p->heredoc)
		free(p->heredoc);
	if (parsed_input)
		free_arr(parsed_input);
	if (input)
		free(input);
	p->heredoc = NULL;
	parsed_input = NULL;
	input = NULL;
}
