/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:29:25 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/12 13:35:47 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_params(t_pipehelper *params)
{
	params->input1 = NULL;
	params->cmd = NULL;
	params->paths = NULL;
	params->fd_in = NULL;
	params->fd_out = NULL;
	params->i = 0;
	params->num_in = 1;
	params->num_out = 0;
	params->fd_index = 0;
	params->fd_outdex = 0;
	return (1);
}

int	is_unclosed(char *input)
{
	while (*input)
	{
		if (is_apo(*input))
		{
			if (apo_count(input + 1, *input))
				input += mod_ft_strlen(input + 1, *input) + 2;
			else
				return (1);
		}
		input++;
	}
	return (0);
}

char	*get_input(int unclosed)
{
	char	*tmp;
	char	*tmp2;
	char	*ret;
	int		size;
	int		line_count;

	line_count = 0;
	ret = NULL;
	tmp2 = NULL;
	while (unclosed)
	{
		if (!line_count)
			tmp = readline("minishell % ");
		else
			tmp = readline("dquote> ");
		if (ret)
			tmp2 = ft_strdup(ret);
		if (ret)
			free(ret);
		size = ft_strlen(tmp) + ft_strlen(tmp2) + 1;
		ret = malloc(size);
		ft_strlcat(ret, tmp2, size);
		ft_strlcat(ret, tmp, size);
		if (tmp)
			free(tmp);
		if (tmp2)
			free(tmp2);
		unclosed = is_unclosed(ret);
		line_count++;
	}
	ret[size] = 0;
	return (ret);
}
