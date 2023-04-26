/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:29:25 by awilliam          #+#    #+#             */
/*   Updated: 2023/04/26 13:16:57 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_unclosed(char *input)
{
	if (!input)
		return (0);
	while (*input)
	{
		if (is_apo(*input))
		{
			if (apo_count(input + 1, *input))
				input += ft_strlenc(input + 1, *input) + 1;
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
		if (!tmp)
		{
			ft_putstr_fd("\033[Fminishell % exit\n", 2);
			return (NULL);
		}
		if (ret)
			tmp2 = ft_strjoin(ret, "\n");
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
