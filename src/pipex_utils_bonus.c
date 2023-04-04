/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:16:23 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/01 12:23:20 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bonus_error_handler(char *s, t_pipexhelper *params, int *pipe)
{
	if (pipe)
		free(pipe);
	if (params)
		free_arrs(params);
	perror(s);
	exit(1);
}

void	close_pipes(int *pipe, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(pipe[i]);
		i++;
	}
}

static int	init_bonus_helper(t_pipexhelper *params, char **envp)
{
	params->paths = get_path(envp);
	if (!params->paths)
	{
		free_arrs(params);
		error_handler("allocation failed", params);
		return (0);
	}
	params->input1 = NULL;
	params->input2 = NULL;
	params->cmd = NULL;
	params->cmd2 = NULL;
	return (1);
}

int	init_bonus(t_pipexhelper *params, char **envp, char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!*argv[i])
		{
			ft_putstr_fd("Error: Empty input!", 2);
			exit(1);
		}
		i++;
	}
	params->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (params->fd_out == -1)
		file_error(argv[argc - 1], -1, 1, NULL);
	params->fd_in = open(argv[1], O_RDONLY);
	if (params->fd_in == -1)
	{
		file_error(argv[1], params->fd_out, 0, NULL);
		return (0);
	}
	params->argc = argc;
	if (!init_bonus_helper(params, envp))
		return (0);
	return (1);
}
