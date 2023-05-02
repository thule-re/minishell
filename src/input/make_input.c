/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:17:09 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/02 18:06:52 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	are_there_pipes(char **parsed_input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (parsed_input[i])
	{
		if (!ft_strncmp("|", parsed_input[i], 2))
			count++;
		i++;
	}
	return (count);
}

int	make_count(t_minishell *p, char **parsed_input, int index)
{
	int	count;

	if (!are_there_pipes(parsed_input))
		p->pipe_status = 4;
	else if (index == 0)
		p->pipe_status = 1;
	else if (are_there_pipes(&parsed_input[index]))
		p->pipe_status = 2;
	else
		p->pipe_status = 3;
	count = 0;
	while (parsed_input[index])
	{
		if (!ft_strncmp("|", parsed_input[index], 2))
			break ;
		count++;
		index++;
	}
	return (count);
}

void	add_fds(t_minishell *p, char **arr, int index, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (!(ft_strncmp("<", arr[index + i], 2)))
			p->fd_in = open(arr[index + i + 1], O_RDONLY);
		if (!(ft_strncmp("<<", arr[index + i], 3)))
			p->fd_in = 0;
		if (!(ft_strncmp(">", arr[index + i], 2)))
			p->fd_out = open(arr[index + i + 1], \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (!(ft_strncmp(">>", arr[index + i], 3)))
			p->fd_out = open(arr[index + i + 1], \
				O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (p->fd_in == -1)
			return(file_error(arr[index + i + 1], p->fd_in, 1, p));
		if (p->fd_out == -1)
			return(file_error(arr[index + i + 1], p->fd_out, 1, p));
	}
}

//pipe status: 1 = at beginning, 2 = middle, 3 = end, 4 = no pipes
void	make_input(t_minishell *p, char **arr, int index)
{
	int	count;
	int	i;
	int	j;

	i = -1;
	j = 0;
	count = make_count(p, arr, index);
	p->input1 = malloc(sizeof(char *) * (count + 1));
	add_fds(p, arr, index, count);
	if (!p->input1)
		return ;
	while (++i < count)
	{
		if (!ft_strncmp("<", arr[index + i], 2) || !ft_strncmp(">", arr[index + i], 2) \
				|| !ft_strncmp("<<", arr[index + i], 3) || !ft_strncmp(">>", arr[index + i], 3))
			i++;
		else
			p->input1[j++] = ft_strdup(arr[index + i]);
		if (i < count && is_special_char(arr[index + i]))
			string_shift(p->input1[j - 1]);
	}
	p->input1[j] = 0;
	if (p->heredoc && !(check_access(p->input1)) && !p->fd_in)
	{	
		pipe(&p->hd_pipe[0]);
		write(p->hd_pipe[1], p->heredoc, ft_strlen(p->heredoc));
		close(p->hd_pipe[1]);
	}
	p->cmd = get_command(p->paths, p->input1[0]);
}
