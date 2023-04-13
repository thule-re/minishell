/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:29:25 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/13 10:50:39 by awilliam         ###   ########.fr       */
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
	params->heredoc = NULL;
	params->delim = NULL;
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
				input += mod_ft_strlen(input + 1, *input) + 1;
			else
				return (1);
		}
		input++;
	}
	return (0);
}

char	*remove_delim(char *s, char *loc, int delim_len)
{
	char	*new;
	int		i;
	char	*tmp;

	i = 0;
	new = malloc(ft_strlen(s) - delim_len);
	tmp = s;
	while (*s)
	{
		if (s == loc)
			s += delim_len;
		new[i] = *s;
		i++;
		s++;
	}
	free(tmp);
	new[i] = 0;
	return (new);
}

char	*get_input(int unclosed, t_pipehelper *p, char *tmp, char *tmp2)
{
	char	*ret;
	int		line_count;

	line_count = 0;
	ret = NULL;
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
		ret = ft_strjoin(tmp2, tmp);
		if (tmp)
			free(tmp);
		if (tmp2)
			free(tmp2);
		unclosed = is_unclosed(ret);
		line_count++;
	}
	return (delimit_this(ret, p));
}
