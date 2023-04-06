/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:29:25 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/06 10:01:56 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_params(t_pipehelper *params)
{
	params->input1 = NULL;
	params->cmd = NULL;
	params->paths = NULL;
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

	ret = NULL;
	tmp2 = NULL;
	while (unclosed)
	{
		tmp = readline("minishell % ");
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
	}
	return (ret);
}
