/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:17:09 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/13 16:43:55 by awilliam         ###   ########.fr       */
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

int	make_count(t_pipehelper *p, char **parsed_input, int index)
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

int	count_string(char **arr, int index, int count, char c)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < count)
	{
		if (arr[index + i][0] == c && arr[index + i][1] != c)
			ret++;
		i++;
	}
	return (ret);
}

void	add_fds(t_pipehelper *p, char **arr, int index, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (arr[index + i][0] == '<' && arr[index + i][1] != '<')
			p->fd_in = open(&arr[index + i][1], O_RDONLY);
		if (arr[index + i][0] == '<' && arr[index + i][1] == '<')
			p->fd_in = 0;
		if (arr[index + i][0] == '>' && arr[index + i][1] != '>')
			p->fd_out = open(&arr[index + i][1], \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (arr[index + i][0] == '>' && arr[index + i][1] == '>')
			p->fd_out = open(&arr[index + i][2], \
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
}

//pipe status: 1 = at beginning, 2 = middle, 3 = end, 4 = no pipes
void	make_input(t_pipehelper *p, char **arr, int index)
{
	int	count;
	int	i;
	int	j;

	i = -1;
	j = 0;
	count = make_count(p, arr, index);
	p->input1 = malloc(sizeof(char *) * (count + 1));
	add_fds(p, arr, index, count);
	while (++i < count)
	{
		if (arr[index + i][0] != '<' && arr[index + i][0] != '>')
			p->input1[j++] = ft_strdup(arr[index + i]);
	}
	p->input1[j] = 0;
	if (p->heredoc && !(check_access(p->input1)) && !p->fd_in)
	{	
		pipe(&p->hd_pipe[0]);
		write(p->hd_pipe[1], p->heredoc, ft_strlen(p->heredoc));
		close(p->hd_pipe[1]);
	}
	p->input1[j] = 0;
}
