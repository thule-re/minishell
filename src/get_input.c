/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:29:25 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/01 12:28:01 by treeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_unclosed(char *input)
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

static char	*exit_signal(void)
{
	ft_putstr_fd("\033[Fminishell % exit\n", 2);
	return (NULL);
}

static char	*unexpected_eof(void)
{
	ft_putstr_fd("unexpected EOF while looking for matching `'", 2);
	ft_putchar_fd('"', 2);
	ft_putstr_fd("\n", 2);
	g_es = 258;
	return (ft_strdup(""));
}

char	*get_input(t_minishell *p, char *tmp, char *tmp2, int line_count)
{
	char	*ret;

	ret = NULL;
	while (1)
	{
		if (!line_count)
			tmp = readline("minishell % ");
		else
			tmp = readline("dquote> ");
		if (!tmp && !line_count)
			return (exit_signal());
		else if (!tmp && line_count)
			return (unexpected_eof());
		if (ret)
			tmp2 = ft_strjoin(ret, "\n");
		if (ret)
			free(ret);
		ret = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
		if (!is_unclosed(ret))
			break ;
		line_count++;
	}
	return (delimit_this(ret, p));
}
