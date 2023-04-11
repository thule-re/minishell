/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:17:09 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/11 08:49:23 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	count_string(char **parsed_input, int index, int count, char *s)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < count)
	{
		if (!ft_strncmp(s, parsed_input[index + i], ft_strlen(s)))
			ret++;
		i++;
	}
	return (ret);
}

void	add_fds(t_pipehelper *p, char **parsed_input, int index, int count)
{
	int	i;
	int	j;
	int	k;

	p->num_in = count_string(parsed_input, index, count, "<");
	p->num_out = count_string(parsed_input, index, count, ">");
	i = 0;
	j = 0;
	k = 0;
	if (p->num_in)
		p->fd_in = malloc(sizeof(int) * p->num_in);
	if (p->num_out)
		p->fd_out = malloc(sizeof(int) * p->num_out);
	while (i < count)
	{
		if (!ft_strncmp("<", parsed_input[index + i], 1))
		{
			p->fd_in[j] = open(&parsed_input[index + i][1], O_RDONLY);
			j++;
		}
		if (!ft_strncmp(">", parsed_input[index + i], 1))
		{
			p->fd_out[k] = open(&parsed_input[index + i][1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			k++;
		}
		i++;
	}
}

//pipe status: 1 = at beginning, 2 = middle, 3 = end, 4 = no pipes
void	make_input(t_pipehelper *p, char **parsed_input, int index)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	j = 0;
	count = make_count(p, parsed_input, index);
	p->input1 = malloc(sizeof(char *) * (count + 1));
	add_fds(p, parsed_input, index, count);
	while (i < count)
	{
		if (ft_strncmp("<", parsed_input[index + i], 1) && ft_strncmp(">", parsed_input[index + i], 1))
		{
			p->input1[j] = ft_strdup(parsed_input[index + i]);
			j++;
		}
		i++;
	}
	p->input1[i] = 0;
}
