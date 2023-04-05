/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:16:23 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/05 13:46:23 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	init_param_helper(t_pipehelper *params)
{
	if (!params->paths || !params->input1)
		error_handler("allocation failed", params);
	params->cmd = get_command(params->paths, params->input1[0]);
	if (!params->cmd || !params->cmd2)
		error_handler("allocation failed", params);
	return (1);
}

int	init_params(t_pipehelper *params, char **envp, char **argv)
{
	if (!*argv[1] || !*argv[2] || !*argv[3] || !*argv[4])
	{
		ft_putstr_fd("Error: Empty input!", 2);
		exit(1);
	}
	params->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (params->fd_out == -1)
		file_error(argv[4], -1, 1, NULL);
	params->fd_in = open(argv[1], O_RDONLY);
	if (params->fd_in == -1)
		file_error(argv[1], params->fd_out, 0, NULL);
	params->input1 = ft_shell_split(argv[2], ' ');
	params->paths = get_path(envp);
	if (!init_param_helper(params))
		return (0);
	return (1);
}
