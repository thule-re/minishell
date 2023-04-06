/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:17:09 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/06 09:17:57 by awilliam         ###   ########.fr       */
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

int	make_count(char **parsed_input, int index)
{
	int	count;

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

//pipe status: 1 = at beginning, 2 = middle, 3 = end, 4 = no pipes
void	make_input(t_pipehelper *p, char **parsed_input, int index)
{
	int	count;
	int	i;

	i = 0;
	count = make_count(parsed_input, index);
	p->input1 = malloc(sizeof(char *) * (count + 1));
	while (i < count)
	{	
		p->input1[i] = ft_strdup(parsed_input[index + i]);
		i++;
	}
	p->input1[i] = 0;
	if (!are_there_pipes(parsed_input))
		p->pipe_status = 4;
	else if (index == 0)
		p->pipe_status = 1;
	else if (are_there_pipes(&parsed_input[index]))
		p->pipe_status = 2;
	else
		p->pipe_status = 3;
}
